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

<img src="{“PDI-2023.2”}/imgs/p1.1.PNG" alt="ex1-original" width = 250px> <img src="/imgs/p1.2.PNG" alt="ex1-original" width = 250px>


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

# Prática 5 - HISTOGRAMA & EQUALIZAÇÃO
A prática a seguir tem como objetivo principal a implementação de um programa que utiliza como base a web cam para capturar imagens e realizar a equalização do histograma. Para meu caso, não foi possível utilizar a web cam por conta de algumas limitações do meu ambiente, então utilizei a mesma imagem base utilizada nos exemplos anteriores. O programa teve como base o exemplo histogram.cpp e basicamente extrai o histograma da imagem original grayscale e em seguida realiza a equalização, criando um novo histograma para a imagem equalizada. A equalização do histograma é facilmente realizada através da função equalizeHist.

~~~c++

    int histw = nbins, histh = nbins / 2;
    Mat histImgegray(histh, histw, CV_8UC1, Scalar(0));
    Mat histImgequalizado(histh, histw, CV_8UC1, Scalar(0));

    while (1) {
        image.copyTo(gray);

        // Calculando histograma da imagem em escala de cinza original
        calcHist(&gray, 1, 0, Mat(), histgray, 1,
                 &nbins, &histrange,
                 uniform, acummulate);

        normalize(histgray, histgray, 0, histImgegray.rows, cv::NORM_MINMAX, -1, cv::Mat());

        histImgegray.setTo(Scalar(0));

        for(int i=0; i<nbins; i++){
          line(histImgegray,
               Point(i, histh),
               Point(i, histh-cvRound(histgray.at<float>(i))),
               Scalar(255), 1, 8, 0);
        }

        histImgegray.copyTo(gray(Rect(0, 0, nbins, histh)));

        imshow("Grayscale", gray);

        // Equalizar histograma
        equalizeHist(image, iequalizado);

        // Calculando histograma da imagem equalizada
        calcHist(&iequalizado, 1, 0, Mat(), histequalizado, 1, &nbins, &histrange, uniform, acummulate);

        // Normalizando
        normalize(histequalizado, histequalizado, 0, histImgequalizado.rows, NORM_MINMAX, -1, Mat());

        histImgequalizado.setTo(Scalar(0));

        for (int i = 0; i < nbins; i++) {
            line(histImgequalizado,
                Point(i, histh),
                Point(i, histh - cvRound(histequalizado.at<float>(i))),
                Scalar(255, 255, 255), 1, 8, 0);
        }

        histImgequalizado.copyTo(iequalizado(Rect(0, 0, nbins, histh)));

        imshow("Imagem Equalizada", iequalizado);

        key = waitKey(30);
        if (key == 27) break;
    }
    return 0;
}

~~~

Com o código aplicado temos o seguinte resultado de saída para a imagem ghibli.png: 

<img src="/imgs/histo_grayscale.PNG" alt="ex1-original" width = 250px> <img src="/imgs/histo_equalize.PNG" alt="ex1-original" width = 250px> 


# Prática 6 - FILTROS LAPLACIANO E LAPLACIANO DO GAUSSIANO
Para esta prática foi utilizado como referência o código filtroespacial.cpp, cuja funcionalidade conta com diversos filtros de imagem. O objetivo era implementar um filtro Laplaciano do gaussiano, e comparar com o filtro Laplaciano, que já estava implementado no código original.
~~~c++

#include <iostream>
#include <opencv2/opencv.hpp>

void printmask(cv::Mat &m) {
  for (int i = 0; i < m.size().height; i++) {
    for (int j = 0; j < m.size().width; j++) {
      std::cout << m.at<float>(i, j) << ",";
    }
    std::cout << "\n";
  }
}

int main(int, char ** argv) {
  cv::Mat image, framegray, frame32f, frameFiltered;
  float media[] = {0.1111, 0.1111, 0.1111, 0.1111, 0.1111,
                   0.1111, 0.1111, 0.1111, 0.1111};
  float gauss[] = {0.0625, 0.125,  0.0625, 0.125, 0.25,
                   0.125,  0.0625, 0.125,  0.0625};
  float horizontal[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
  float vertical[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
  float laplacian[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
  float boost[] = {0, -1, 0, -1, 5.2, -1, 0, -1, 0};
  float laplgauss [] ={0,0,-1,0,0,0,-1,-2,-1,0,-1,-2,16,-2,-1,
                      0,-1,-2,-1,0,0,0,-1,0,0};
  cv::Mat mask(3, 3, CV_32F), mask_scale;
  cv::Mat result;
  int absolut;
  char key;

  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE); // Carregar a imagem em escala de cinza
  if (!image.data) {
    std::cout << "Erro ao abrir a imagem" << std::endl;
    return -1;
  }

  cv::namedWindow("filtro aplicado", cv::WINDOW_NORMAL);
  cv::namedWindow("original", cv::WINDOW_NORMAL);

  mask = cv::Mat(3, 3, CV_32F, media); // Inicializar a máscara
  absolut = 1; // Calcula o valor absoluto da imagem

  for (;;) {
    cv::imshow("original", image);
    image.convertTo(frame32f, CV_32F);
    cv::filter2D(frame32f, frameFiltered, frame32f.depth(), mask, cv::Point(1, 1), 0);
    if (absolut) {
      frameFiltered = cv::abs(frameFiltered);
    }

    frameFiltered.convertTo(result, CV_8U);

    cv::imshow("filtro aplicado", result);

    key = (char)cv::waitKey(10);
    if (key == 27) break; // Tecla Esc pressionada!
    switch (key) {
      case 'a':
        absolut = !absolut;
        break;
      case 'm':
        mask = cv::Mat(3, 3, CV_32F, media);
        printmask(mask);
        break;
      case 'g':
        mask = cv::Mat(3, 3, CV_32F, gauss);
        printmask(mask);
        break;
      case 'h':
        mask = cv::Mat(3, 3, CV_32F, horizontal);
        printmask(mask);
        break;
      case 'v':
        mask = cv::Mat(3, 3, CV_32F, vertical);
        printmask(mask);
        break;
      case 'l':
        mask = cv::Mat(3, 3, CV_32F, laplacian);
        printmask(mask);
        break;
        case 'p':
        mask = cv::Mat(5, 5, CV_32F, laplgauss);
        printmask(mask);
        break;
      case 'b':
        mask = cv::Mat(3, 3, CV_32F, boost);
        break;
      default:
        break;
    }
  }
  return 0;
}
~~~

Como resultado é perceptível que o filtro Laplaciano do gaussiano possui maior atenuação nas regições de contorno da imagem, intensificando as bordas em comparação ao filtro gaussiano mais simples. Isso ocorre pois esse filtro funciona de forma a primeiro suavizar a imagem atraves do filtro gaussiano, o que torna as bordas mais nítidas e mais proeminentes devido ao efeito de suavização, e logo após é aplicado o Laplaciano, que detecta as bordas com mais precisão devido ao efeito do gaussiano.

	
<img src="/imgs/mean_filter.PNG" alt="ex1-original" width = 250px> + <img src="/imgs/lap_filter.PNG" alt="ex1-original" width = 250px> = <img src="/imgs/lapgauss_filter.PNG" alt="ex1-original" width = 250px> 
