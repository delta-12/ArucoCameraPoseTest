#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/aruco.hpp>

int main(int argc, char **argv)
{

    // Get predefined dictionary
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);

    cv::Mat image, imageCopy;

    image = cv::imread("img.png");
    image.copyTo(imageCopy);

    // Vec to store ids
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;
    cv::aruco::detectMarkers(image, dictionary, corners, ids);

    // If at least one marker detected
    if (ids.size() > 0)
    {
        cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
    }

    // Save image
    cv::imwrite("detect-markers.png", imageCopy);

    return 0;
}