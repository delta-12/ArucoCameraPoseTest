#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/aruco.hpp>

int main(int argc, char **argv)
{
    // Configure video input
    cv::VideoCapture inputVideo;
    inputVideo.open(2);

    // Get predefined dictionary
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);

    while (inputVideo.grab())
    {
        cv::Mat image, imageCopy;

        inputVideo.retrieve(image);
        image.copyTo(imageCopy);

        // Vec to store ids
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f>> corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);

        // if at least one marker detected
        if (ids.size() > 0)
            cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);

        cv::resize(imageCopy, imageCopy, cv::Size(), 0.6, 0.6);

        // Dispaly the image
        cv::imshow("out", imageCopy);
        char key = (char)cv::waitKey(1);

        if (key == 27)
            break;
    }

    return 0;
}