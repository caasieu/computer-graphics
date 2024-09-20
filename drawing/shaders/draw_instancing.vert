#version 430 core

layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 vertex_color;

// view matrix vindo do C++
uniform mat4 v_matrix;
uniform mat4 proj_matrix;
uniform float tf;   // time factor for animation and placing the cubes

//out vec3 sent_color;
out vec4 varyingColor;

// will need to create the rotations here for each new instanced object
mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);


void main(void) {

    float i = gl_InstanceID + tf; // value based on time factor 
    float a = sin(203.0 * i/8000.0) * 403.0;
    float b = sin(301.0 * i/4001.0) * 401.0;
    float c = sin(400.0 * i/6003.0) * 405.0;
    
    // build the rotation and translation matrices to be applied to this cube’s model matrix
    mat4 localRotX = buildRotateX(1000*i);
    mat4 localRotY = buildRotateY(1000*i);
    mat4 localRotZ = buildRotateZ(1000*i);
    mat4 localTrans = buildTranslate(a,b,c);

    // build the model matrix
    mat4 newM_matrix = localTrans * localRotX * localRotY * localRotZ;
    mat4 mv_matrix = v_matrix * newM_matrix;

    //sent_color = vertex_color;
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
}


// builds and returns a translation matrix
mat4 buildTranslate(float x, float y, float z) { 
  mat4 trans = mat4(
    1.0, 0.0, 0.0, 0.0,
	  0.0, 1.0, 0.0, 0.0,
	  0.0, 0.0, 1.0, 0.0,
	  x, y, z, 1.0 
  );
  
  return trans;
}

// builds and returns a matrix that performs a rotation around the X axis
mat4 buildRotateX(float rad) { 
  mat4 xrot = mat4(
    1.0, 0.0, 0.0, 0.0,
	  0.0, cos(rad), -sin(rad), 0.0,
	  0.0, sin(rad), cos(rad), 0.0,
	  0.0, 0.0, 0.0, 1.0 
  );
    
  return xrot;
}

// builds and returns a matrix that performs a rotation around the Y axis
mat4 buildRotateY(float rad)
{ 
  mat4 yrot = mat4(
    cos(rad), 0.0, sin(rad), 0.0,
		0.0, 1.0, 0.0, 0.0,
		-sin(rad), 0.0, cos(rad), 0.0,
		0.0, 0.0, 0.0, 1.0 
  );

  return yrot;
}

// builds and returns a matrix that performs a rotation around the Z axis
mat4 buildRotateZ(float rad) { 
  mat4 zrot = mat4(
    cos(rad), -sin(rad), 0.0, 0.0,
		sin(rad), cos(rad), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0 
  );

  return zrot;
}

// builds and returns a scale matrix
mat4 buildScale(float x, float y, float z) { 
  mat4 scale = mat4(
    x, 0.0, 0.0, 0.0,
		0.0, y, 0.0, 0.0,
		0.0, 0.0, z, 0.0,
		0.0, 0.0, 0.0, 1.0 
  );

  return scale;
}