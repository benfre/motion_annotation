/* box_selection.cpp
 *
 * Copyright (C) 2014 Santosh Thoduka
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <motion_annotation/box_selection.h>
#include <iostream>

BoxSelection::BoxSelection() : is_satisfied_(false)
{

}

BoxSelection::~BoxSelection()
{
}

void BoxSelection::selectBox(cv::Mat &frame, const cv::Mat &previous_frame, cv::Point &top_left, cv::Point &bottom_right)
{
    cv::imshow("Box Selection", frame);
    cv::moveWindow("Box Selection", 700, 10);
    cv::setMouseCallback("Box Selection", mouseCallback, this);

    while (!is_satisfied_)
    {        
        received_top_left_ = false;
        received_bottom_right_ = false;
        top_left_.x = 0.0;
        top_left_.y = 0.0;
        bottom_right_.x = 0.0;
        bottom_right_.y = 0.0;
        frame.copyTo(frame_);
        cv::imshow("Box Selection", frame_);
        cv::moveWindow("Box Selection", 700, 10);
        cv::waitKey(1);

        char key;
        while (!received_bottom_right_)
        {
            key = cv::waitKey(30);
            if (key == '1')
            {
                cv::imshow("Box Selection", frame_);
                cv::moveWindow("Box Selection", 700, 10);
            }
            else if (key == '2')
            {
                cv::imshow("Box Selection", previous_frame);
                cv::moveWindow("Box Selection", 700, 10);
            }
            else if (key == 'x')
            {
                break;
            }
        }
        if (received_bottom_right_)
        {
            cv::rectangle(frame_, top_left_, bottom_right_, cv::Scalar(0,0,255), 2,8, 0);
            cv::imshow("Box Selection", frame_);
            cv::moveWindow("Box Selection", 700, 10);
            cv::waitKey(1);
        }
        else
        {
            break;
        }

        if ((key = cv::waitKey(0)) == 'y')break;
        else continue;
    }
    cv::destroyWindow("Box Selection");
    frame_.copyTo(frame);
    top_left = top_left_;
    bottom_right = bottom_right_;
}

void BoxSelection::mouseCallback(int event, int x, int y, int flags, void *param)
{
    BoxSelection *this_obj = static_cast<BoxSelection*>(param);
    this_obj->doMouseCallback(event, x, y, flags);
}

void BoxSelection::doMouseCallback(int event, int x, int y, int flags)
{
    if (event == CV_EVENT_LBUTTONDOWN)
    {
        if (!received_top_left_)
        {
            top_left_.x = x;
            top_left_.y = y;
            received_top_left_ = true;
            std::cout << "received top left "<< std::endl;
        }
        else if (!received_bottom_right_)
        {
            bottom_right_.x = x;
            bottom_right_.y = y;
            received_bottom_right_ = true;
            std::cout << "received br "<< std::endl;
        }
    }
}
