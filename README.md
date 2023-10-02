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

<img src="/imgs/p1.1.PNG" alt="ex1-original" width = 250px> <img src="/imgs/p1.2.PNG" alt="ex1-original" width = 250px>


# Prática 2 - TROCAR REGIÕES

A segunda prática tem como objetivo dividir a imagem original em 4 partes iguais e inverter o quadrante destas partes. Para isso foram utilizados recursos da classe Mat, como a rect() que facilitou armazenar cada pedaço da imagem em uma variável para posteriormente ser utilizada na imagem final, através da função copyTo().

~~~c++
  //São definidas as 4 divisões da foto, resultando em 4 imagens, cada uma com uma parte retângular
  Mat part1 = image(Rect(0,0,image.rows/2,image.cols/2));
  Mat part2 = image(Rect(image.rows/2,0,image.rows/2,image.cols/2));
  Mat part3 = image(Rect(0,image.cols/2,image.rows/2,image.cols/2));
  Mat part4 = image(Rect(image.rows/2,image.cols/2,image.rows/2,image.cols/2));

  part1.copyTo(img_embaralhada(Rect(image.rows/2,image.cols/2,image.rows/2,image.cols/2)));
  part2.copyTo(img_embaralhada(Rect(0,image.cols/2,image.rows/2,image.cols/2)));
  part3.copyTo(img_embaralhada(Rect(image.rows/2,0,image.rows/2,image.cols/2)));
  part4.copyTo(img_embaralhada(Rect(0,0,image.rows/2,image.cols/2)));
~~~

<img src="/imgs/p1.1.PNG" alt="ex1-original" width = 250px> <img src="/imgs/P2.1.PNG" alt="ex1-original" width = 250px>


# Prática 3 - ESTEGANOGRAFIA

Em resumo, a esteganografia se baseia em “criptografar” uma imagem dentro de outra, de forma que só uma delas fique visível. A técnica utilizada na disciplina, vista no exemplo “esteg-encode.cpp”, se baseia em codificar as imagens a partir da manipulação do conteúdo presente nos pixels da imagem, a partir da ordem de significância. Dada essa introdução foi proposta a decodificação da seguinte figura, que possui uma imagem oculta entre seus pixels.

<img src="/imgs/cod_img.PNG" alt="ex1-original" width = 250px>

Para a figura em questão, após montado o código e realizando alguns testes, percebeu-se que a figura oculta estava presente nos 3 bits menos significativos da imagem codificada. Dessa forma a figura original é representada pelos 5 bits mais significativos, e a figura escondida é representada pelos 3 bits menos significativos.
~~~c++
    img_decoded = img_encoded.clone();

    for (int i = 0; i < img_encoded.rows; i++) {
        for (int j = 0; j < img_encoded.cols; j++) {
            val_encoded = img_encoded.at<Vec3b>(i, j);

            val_decoded[0] = val_encoded[0] << (8-nbits);
            val_decoded[1] = val_encoded[1] << (8-nbits);
            val_decoded[2] = val_encoded[2] << (8-nbits);

            img_decoded.at<Vec3b>(i, j) = val_decoded;
        }
    }
~~~

<img src="/imgs/cod_img.PNG" alt="ex1-original" width = 250px> <img src="/imgs/decod_img.PNG" alt="ex1-original" width = 250px>
