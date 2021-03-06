//******************************************************************************
//* Copyright (c) Jon Newman (jpnewman at mit snail edu) 
//* All right reserved.
//* This file is part of the Simple Tracker project.
//* This is free software: you can redistribute it and/or modify
//* it under the terms of the GNU General Public License as published by
//* the Free Software Foundation, either version 3 of the License, or
//* (at your option) any later version.
//* This software is distributed in the hope that it will be useful,
//* but WITHOUT ANY WARRANTY; without even the implied warranty of
//* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//* GNU General Public License for more details.
//* You should have received a copy of the GNU General Public License
//* along with this source code.  If not, see <http://www.gnu.org/licenses/>.
//******************************************************************************

#ifndef CAMERA_H
#define	CAMERA_H


#include <opencv2/opencv.hpp>

#include "../../lib/shmem/MatServer.h"

/**
 * Abstract base class to be implemented by any Camera Server within the Simple
 * Tracker project.
 * @param image_sink_name Image SINK name.
 */
class Camera {
public:
    
    Camera(std::string image_sink_name) : 
      name(image_sink_name)
    , frame_sink(image_sink_name) { }
    
    // Cameras must be able to serve cv::Mat frames
    virtual void serveMat(void) = 0;
    
    // Cameras allow image undistortion if parameters are provided
    void undistortMat(void) {
        if (undistort_image) {
            cv::undistort(current_frame, current_frame, camera_matrix, distortion_coefficients);
        }
    }
    
    // Cameras must be able to obtain a cv::Mat from some source (physical camera, file, etc)
    virtual void grabMat(void) = 0;
    
    // Cameras must be configurable via file
    virtual void configure(void) = 0;
    virtual void configure(std::string file_name, std::string key) = 0;
    
    // Users should be able to access current frame (without serving)
    cv::Mat getCurrentFrame(void) { return current_frame; }
    
    // Cameras must be interruptable
    void stop(void) { frame_sink.set_running(false); }
    
protected:
    
    // cv::Mat server for sending frames to shared memory
    MatServer frame_sink;
    std::string name;
    
    // Cameras have a region of interest to crop images
    cv::Rect region_of_interest;
    
    // Currently acquired frame
    cv::Mat current_frame;

    // Camera matrix and distortion coefficients. Use to undistort image
    bool undistort_image;
    cv::Mat camera_matrix;
    cv::Mat distortion_coefficients;
    
    // Conversion constants
    cv::Point2f xy_origin_in_px;
    float mm_per_px_y;
    float mm_per_px_x;

};

#endif	/* CAMERA_H */

