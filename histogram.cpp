#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    Mat image, iequalizado, gray;
    Mat histgray;
    Mat histequalizado;
    int nbins = 64;
    float range[] = {0, 255};
    const float *histrange = { range };
    bool uniform = true;
    bool acummulate = false;
    int key;

    image = imread(argv[1], IMREAD_GRAYSCALE); // Carregar a imagem em escala de cinza
    if (!image.data) {
        cout << "Erro ao abrir a imagem" << std::endl;
        return -1;
    }

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
