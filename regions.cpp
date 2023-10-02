#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char** argv){
  Mat image;
  int px1,py1,px2,py2;


  image = imread(argv[1],IMREAD_GRAYSCALE);

  if(!image.data){
    cout << "Erro ao abrir a imagem" << std::endl;
  }
  namedWindow("Imagem Original",WINDOW_AUTOSIZE);
  imshow("Imagem Original", image);

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
    namedWindow("Negativo", WINDOW_AUTOSIZE);
    imshow("Negativo", image);
    imwrite("imagem_negativa.png",image);	
    waitKey(); 
       
  }else{
    cout<<"As coordenadas inseridas não estão dentro das proporções da imagem ou possuem valores incosistentes.";
  }

  return 0;
}