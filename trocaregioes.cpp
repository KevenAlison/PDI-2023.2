#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char** argv){
  Mat image;
  image = imread(argv[1],IMREAD_GRAYSCALE);
  //cria uma imagem com proporções e tipo iguais à original
  Mat img_embaralhada(image.rows,image.cols,image.type());
  if(!image.data){
    cout << "Erro ao abrir a imagem" << std::endl;
  }

  //São definidas as 4 divisões da foto, resultando em 4 imagens, cada uma com uma parte retângular
  Mat part1 = image(Rect(0,0,image.rows/2,image.cols/2));
  Mat part2 = image(Rect(image.rows/2,0,image.rows/2,image.cols/2));
  Mat part3 = image(Rect(0,image.cols/2,image.rows/2,image.cols/2));
  Mat part4 = image(Rect(image.rows/2,image.cols/2,image.rows/2,image.cols/2));

  part1.copyTo(img_embaralhada(Rect(image.rows/2,image.cols/2,image.rows/2,image.cols/2)));
  part2.copyTo(img_embaralhada(Rect(0,image.cols/2,image.rows/2,image.cols/2)));
  part3.copyTo(img_embaralhada(Rect(image.rows/2,0,image.rows/2,image.cols/2)));
  part4.copyTo(img_embaralhada(Rect(0,0,image.rows/2,image.cols/2)));

  imshow("Original", image);
  namedWindow("Original",WINDOW_AUTOSIZE);
  namedWindow("Imagem Embaralhada", WINDOW_AUTOSIZE);
  imshow("Imagem Embaralhada", img_embaralhada);
  imwrite("Imagem Embaralhada.png",image);
  waitKey();



  return 0;
}
