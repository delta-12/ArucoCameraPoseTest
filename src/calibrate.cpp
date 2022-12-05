#include <iostream>
#include <string>

#include <opencv2/aruco.hpp>
#include <opencv2/aruco/charuco.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#define CAMERA_WIDTH 4032
#define CAMERA_HEIGHT 3024
#define CHARUCO_IMG_DIR "img/"
const std::string IMGS[] = {"IMG_6708.png", "IMG_6709.png", "IMG_6710.png", "IMG_6711.png", "IMG_6712.png", "IMG_6713.png", "IMG_6714.png", "IMG_6715.png"};

int main(int argc, char **argv)
{
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);   // Get predefined dictionary
    cv::Ptr<cv::aruco::CharucoBoard> board = cv::aruco::CharucoBoard::create(5, 7, 0.04f, 0.01f, dictionary); // Create charuco board
    cv::Size imgSize(CAMERA_WIDTH, CAMERA_HEIGHT);                                                            // Camera image size
    std::vector<std::vector<cv::Point2f>> allCharucoCorners;
    std::vector<std::vector<int>> allCharucoIds;

    // Detect charuco board from several viewpoints and fill allCharucoCorners and allCharucoIds
    for (int i = 0; i < sizeof(IMGS) / sizeof(IMGS[0]); i++)
    {
        std::cout << "Detecting IMG " << i << std::endl;

        cv::Mat image, imageCopy;
        image = cv::imread(CHARUCO_IMG_DIR + IMGS[i]);
        image.copyTo(imageCopy);

        // Detect aruco markers
        std::vector<std::vector<cv::Point2f>> corners;
        std::vector<int> ids;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);

        // If at least one aruco marker id detected
        if (ids.size() > 0)
        {
            cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);

            std::cout << "Corners: " << corners.size() << "\tIds: " << ids.size() << std::endl;

            // Detect charuco corners and ids
            std::vector<cv::Point2f> charucoCorners;
            std::vector<int> charucoIds;
            cv::aruco::interpolateCornersCharuco(corners, ids, image, board, charucoCorners, charucoIds);

            // if at least one charuco id detected
            if (charucoIds.size() > 0)
            {
                cv::aruco::drawDetectedCornersCharuco(imageCopy, charucoCorners, charucoIds, cv::Scalar(255, 0, 0));
                allCharucoCorners.insert(allCharucoCorners.end(), charucoCorners); // add charuco corners to allCharucoCorners
                allCharucoIds.insert(allCharucoIds.end(), charucoIds);             // add charuco ids to allCharucoIds
            }

            // save images with aruco markers and charuco corners and ids drawn on
            std::string imageName = "calibrate_" + std::to_string(i) + ".png";
            cv::imwrite(imageName, imageCopy);
        }
    }

    // Verify number of charuco corners and ids is the same before starting callibration
    if (allCharucoCorners.size() != allCharucoIds.size())
    {
        std::cout << "\nCorner/Id Mismatch!" << std::endl
                  << "Corners: " << allCharucoCorners.size()
                  << "\tIds: " << allCharucoIds.size() << std::endl;
        return -1;
    }

    // Start calibration
    cv::Mat cameraMatrix, distCoeffs;
    std::vector<cv::Mat> rvecs, tvecs;
    int calibrationFlags = 0; // Set calibration flags (same than in calibrateCamera() function)
    double repError = cv::aruco::calibrateCameraCharuco(allCharucoCorners, allCharucoIds, board, imgSize, cameraMatrix, distCoeffs, rvecs, tvecs, calibrationFlags);
    std::cout << "\nRe-production Error: " << repError << std::endl;

    // Save camera calibration to file
    cv::FileStorage file("camera_calibration.yaml", cv::FileStorage::WRITE);
    file << "Camera Matrix" << cameraMatrix;
    file << "Dist Coeffs" << distCoeffs;
    file.release();

    return 0;
}