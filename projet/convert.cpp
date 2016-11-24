///Ce code a été grandement inspiré du code disponible à l'adresse suivante : https://github.com/dbzhang800/QtOpenCV
///Certaines images du dossier STEREO ne sont pas bien converties du format QImage à cv::Mat. Fonction à compléter.

#include "convert.h"

QImage mat2QImage(cv::Mat &mat, QImage::Format format)
{
        return QImage(mat.data, mat.cols, mat.rows,
                      static_cast<int>(mat.step), format);
}

QImage mat2QImage(cv::Mat &mat, bool swap)
{
    switch(mat.type())
    {

        case CV_8UC3 :
        {
            if(swap)
            {
                return mat2QImage(mat, QImage::Format_RGB888).rgbSwapped();
            }
            else
            {
                return mat2QImage(mat, QImage::Format_RGB888);
            }
        }

        case CV_8U :
        {
            return mat2QImage(mat, QImage::Format_Indexed8);
        }

        case CV_8UC4 :
        {
            return mat2QImage(mat, QImage::Format_ARGB32);
        }
    }
    return{};
}

cv::Mat qImage2Mat(QImage &img, int format)
{
    return cv::Mat(img.height(), img.width(),
                   format, img.bits(), img.bytesPerLine());
}

cv::Mat qImage2Mat(QImage &img, bool swap)
{
    if(img.isNull())
    {
        return cv::Mat();
    }

    switch (img.format())
    {
        case QImage::Format_RGB888:
        {
            auto result = qImage2Mat(img, CV_8UC3);
            if(swap)
            {
                cv::cvtColor(result, result, CV_RGB2BGR);
            }
            return result;
        }

        case QImage::Format_Indexed8:
        {
            return qImage2Mat(img, CV_8U);
        }

        case QImage::Format_RGB32:
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:
        {
            return qImage2Mat(img, CV_8UC4);
        }
        default:
            break;
    }
    return {};
}
