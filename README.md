# PDI-2023.2
Repositório para arquivo de práticas e projetos relacionados à disciplina de Processamento digital de imagens.
Discente: [Keven Alison](https://KevenAlison.github.io)

# Prática 1 - REGIONS

Com base no código exemplos/pixels.cpp foi implementado um código que consiste em pegar os pontos definidos pelo usuário na entrada e transformar a região retangular definida por esses dois pontos em uma região negativa. Para isso, foi implementado um for que varre os pixels definidos pela região e define a cor de cada pixel através da função image.at<uchar>.  Para a implementação a imagem foi definida em grayscale para definir a cor máxima como 255, obtendo a cor negativa através da subtração desse valor pelo valor do pixel em grayscale.

~~~c++
  cout << "Cordenada x1: "<<endl;
  cin >> px1;
  cout << "Cordenada y1: "<<endl;
  cin >> py1;
  cout << "Cordenada x2: "<<endl;
  cin >> px2;
  cout << "Cordenada y2: "<<endl;
  cin >> py2;
  
  if(px1!=px2 && py1!=py2 &&px1>=0 && px2<=image.rows && py1>=0 && py2<=image.rows){
    for(int i=px1;i<px2;i++){
      for(int j=py1;j<py2;j++){
        image.at<uchar>(i,j)=255 - image.at<uchar>(i,j);
      }
    }
~~~

<img src="/imgs/p1.1.png" alt="ex1-original" width = 350px>
<img src="/imgs/p1.2.png" alt="ex1-original" width = 350px>
