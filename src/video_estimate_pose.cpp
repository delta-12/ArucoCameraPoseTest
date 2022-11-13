#include <string>

#include <opencv2/aruco.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#define CAMERA_WIDTH 3840
#define CAMERA_HEIGHT 2160
#define FILE_CAMERA_MATRIX "Camera Matrix"
#define FILE_DIST_COEFFS "Dist Coeffs"
#define OUT_VID_FILE_PREFIX "estimage-pose_"

namespace
{
    const char *about = "Estimate pose from image file with ArUco marker";

    const char *keys =
        "{c         | /path/to/calibration/file.txt | Camera configuration file}"
        "{v         | /path/to/video/file           | Video file}";
}

int main(int argc, char **argv)
{
    // Get command line args
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about(about);
    if (argc != 3)
    {
        parser.printMessage();
        return 0;
    }
    std::string calibrationFile = parser.get<std::string>("c");
    std::string videoFile = parser.get<std::string>("v");

    // Read camera calibration from file
    cv::Mat cameraMatrix, distCoeffs;
    cv::FileStorage inFile(calibrationFile, cv::FileStorage::READ);
    inFile[FILE_CAMERA_MATRIX] >> cameraMatrix;
    inFile[FILE_DIST_COEFFS] >> distCoeffs;
    inFile.release();

    // Get predefined dictionary
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);

    // Read in video
    cv::VideoCapture inputVideo(videoFile);

    // Create output video
    int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    std::string outVideoFile = OUT_VID_FILE_PREFIX + videoFile.substr(videoFile.find_last_of("/\\") + 1);
    cv::Size frameSize(CAMERA_WIDTH, CAMERA_HEIGHT);
    cv::VideoWriter outputVideo(outVideoFile, fourcc, 30, frameSize);

    while (inputVideo.grab())
    {
        // Get frame
        cv::Mat image, imageCopy;
        inputVideo.retrieve(image);
        image.copyTo(imageCopy);

        // Detect ArUco markers
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f>> corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);

        // If at least one marker detected
        if (ids.size() > 0)
        {
            // Draw markers and ids
            cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);

            // Estimate pose
            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(corners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);

            // Draw axis for each marker
            for (int i = 0; i < ids.size(); i++)
            {
                cv::drawFrameAxes(imageCopy, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
            }

            // Add frame to output video
            outputVideo.write(imageCopy);
        }
    }

    outputVideo.release();

    return 0;
}