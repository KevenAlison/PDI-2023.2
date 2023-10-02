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

# Prática 4 - PREENCHIMENTO DE REGIÕES
Para este exercício temos uma imagem com objetos dispostos no espaço. Nosso objetivo é identificar as "bolhas", realizando a contagem de quantas tem buraco e quantas não tem.

<img src="/imgs/bubble1.PNG" alt="ex1-original" width = 250px> 

Vendo a imagem, o primeiro desafio é remover as bolhas que tocam a borda da imagem, pois não da para saber com certeza se há ou não buracos nela, há que não conseguimos ver seu corpo completo. Para eliminar esses objetos foi construída uma lógica que varre as posições correspondentes à borda da imagem, caçando objetos que estejam nesse limite e preenchendos com a cor de fundo, para dar a impressão que foram retirados.
~~~c++
  width=image.cols;
  height=image.rows;
  p.x=0;
  p.y=0;
  n_objremovido = 0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255 && (i == 0 || i == height-1 || j == 0 || j == width-1)){
        n_objremovido++;
        p.x=j;
        p.y=i;
        floodFill(image,p,0);
      }
    }
  }
  image_sborda = image.clone();
~~~

<img src="/imgs/bubble2.PNG" alt="ex1-original" width = 250px> 
Em seguida é utilizado flood fill para identificar e contar a quanmtidade de elementos na imagem
~~~c++

  n_objects = 0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
        // achou um objeto
        n_objects++;
        p.x=j;
        p.y=i;
  	// preenche o objeto com o contador
	floodFill(image,p,n_objects);
      }
    }
  }
  p.x=0;
  p.y=0;
  floodFill(image,p,255);

  int buracos=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 0){
        buracos++;
        p.x=j;
        p.y=i;
		  floodFill(image,p,buracos);
      }
    }
  }
~~~
<img src="/imgs/bubble3.PNG" alt="ex1-original" width = 250px> 
