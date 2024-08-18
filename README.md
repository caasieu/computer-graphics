# This is a bundle of a few OpenGL test projects in C++ 

I decided to touch in a few computer graphics concepts
using OpenGL/GLSL (OpenGL shading language) to deep dive
into the core features and concepts of computer graphics.

the code here is meant to be a recap for me and feel free
to use it for studying, it touches the very basics of
window management, shading language, linear algebra, 
image processing and many more concepts... please be gentle lol!


## This repository uses:
1. C++ as the main Compiling language;
2. GLFW for window management;
3. GLM for mathematical equations and support;
4. SOIL2 for Image loading and saving;
5. CMake for faster compiling and linking;


*testing environment Ubuntu 24.04 LTS, codename: noble*


## Buffers em OpenGL

Em OpenGL, um buffer é uma área de memória usada para armazenar dados relacionados à renderização de gráficos. Existem diferentes tipos de buffers, cada um com uma função específica:

1. **Vertex Buffer (VBO)**: Armazena dados de vértices, como posições, cores, normais, etc., que são usados para desenhar formas geométricas.

2. **Index Buffer (IBO ou EBO)**: Contém índices que apontam para os vértices no VBO, permitindo que você reutilize os mesmos vértices para desenhar formas complexas, como triângulos.

3. **Frame Buffer**: Um buffer que armazena a imagem final ou intermediária que será mostrada na tela. Pode conter vários tipos de dados, como cores, profundidade e stencil.

4. **Depth Buffer**: Usado para armazenar informações de profundidade de cada pixel, ajudando a determinar quais objetos estão na frente ou atrás na cena 3D.

Em resumo, buffers em OpenGL são áreas de memória dedicadas para armazenar dados necessários para a renderização de gráficos, ajudando a organizar e otimizar o processo de desenho na tela.
