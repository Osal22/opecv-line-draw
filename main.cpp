#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <thread>
#include <chrono>

using namespace cv;
using namespace std;

std::vector< pair <cv::Point,cv::Point> > line_vector;//its going to store all the lines in the vector to keep track of lines drawn on the screnn

int x_cursor=0,y_cursor=0,x_button_l=0,y_button_l=0,x_button_r=0,y_button_r=0,clicks_track=0;
std::vector<cv::Point> mouse_event;
std::vector<cv::Point>::iterator mouse_event_itr;
bool draw_status=false,draw_circle=false;
char key_vlaue='a';
cv::Rect bounderies = Rect(0, 0, 10, 50);


struct line_e
{
	int c;
	int m;
	int x;
	int y;
};

std::vector<line_e> line_e_holder;
line_e line_calculated;
line_e line_1;
line_e line_2;

int slope_line(cv::Point first,cv::Point second)
{
	if(second==first)
	{
		return 1;
	}
	else{
		if(second.x-first.x==0)
		{
			return 1;
		}
		else{
		int m=(second.y-first.y)/(second.x-first.x);
		return m;
		}
	}
}

int dist_formula(cv::Point first,cv::Point second)
{
	if(first==second)
	{
		return 1;
	}
	else
	{
	int diff_x=abs(second.x-first.x);
	int diff_y=abs(second.y-first.y);
	int dist= sqrt(diff_x*diff_x+diff_y*diff_y);
	return dist;
	}

}


void draw_cv_vector(cv::Mat img_frame,std::vector<cv::Point> draw_cv_vec_){
	std::vector<cv::Point>::iterator draw_cv_vec_itr;
	if(draw_cv_vec_.size()>=2)
	{
 int i=0;

	for(draw_cv_vec_itr=draw_cv_vec_.begin();draw_cv_vec_itr!=draw_cv_vec_.end();draw_cv_vec_itr++)
	{	
		i++;
		if(i%2==0)
		{
		cv::line(img_frame,*(draw_cv_vec_itr-1),*draw_cv_vec_itr,cv::Scalar(0, 0, 0),1,cv::LINE_8);
		 line_vector.push_back( make_pair(*(draw_cv_vec_itr-1),*draw_cv_vec_itr) );
		}
	}
	}

}


void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
	   	clicks_track++;
        //cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		x_button_l=x;
	    y_button_l=y;
		if(draw_status==true)
		{
		mouse_event.push_back(cv::Point(x,y));
	 	}
	 }
     else if  ( event == EVENT_RBUTTONDOWN )
     {
	    
       
		x_button_r=x;
	    y_button_r=y;
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
          
     }
     else if ( event == EVENT_MOUSEMOVE )
     {
	    
        
		x_cursor=x;
	    y_cursor=y;

     }
}

int main(int argc, char** argv)
{	
	
	while(1)
	{
	auto start_time = std::chrono::high_resolution_clock::now();


		if(mouse_event.size()>1){
			
		}
	// Mat image(500, 500, CV_8UC3,Scalar(23, 78, 0));
	std::string image_path = "/home/goalbytes/_dev/opecv-line-draw/map.pgm";
	Mat image = imread(image_path, IMREAD_COLOR);
	draw_cv_vector(image,mouse_event);
	//std::thread thread_draw(draw_cv_vector,image,mouse_event);
	//thread_draw.join();
	if (!image.data) {
		cout << "Could not open or find"<< " the image";
		return 0;
	}
	Point p1(0, 0), p2(100, 0);
	Point p3(200, 0), p4(500, 500);
	int thickness = 2;
 	namedWindow("Output", cv::WINDOW_NORMAL);
	setMouseCallback("Output", CallBackFunc, NULL);
	std::string draw_status_str=std::to_string(draw_status);
	std::string draw_status_strt="status "+draw_status_str;
	cv::putText(image,draw_status_strt,cv::Point(10,465),cv:: FONT_HERSHEY_COMPLEX_SMALL,1,cv::Scalar(0,255,0),2,false);
	// cv::rectangle(image,)
	if(clicks_track%2==0)
	{
	if(draw_status==true)
	{
	line(image,cv::Point(x_button_l,y_button_l),cv::Point(x_cursor,y_cursor),cv::Scalar(0, 0, 0),1,cv::LINE_8);
	}
	if(draw_circle==true){
		int radius=dist_formula(cv::Point(x_button_l,y_button_l),cv::Point(x_cursor,y_cursor));
		// std::cout<<radius<<std::endl;
	circle(image,cv::Point(x_button_l,y_button_l),radius+1,cv::Scalar(0, 255, 0),1);	
	}
	}

	for(auto itr=mouse_event.begin();itr!=mouse_event.end();itr++)
	{
		int _dist=dist_formula(cv::Point(itr->x,itr->y),cv::Point(x_cursor,y_cursor));
		// std::cout<<_dist<<std::endl;
		if(_dist<2)
		{
			circle(image,cv::Point(itr->x,itr->y),2,cv::Scalar(0, 0, 255),1);	

		}
	}


	// line_e_holder.clear();

	// for(auto itr=line_vector.begin();itr!=line_vector.end();itr++)
	// {
	// 	auto slope_l=slope_line(itr->first,itr->second);
	// 	cv::Point first_point_line=itr->first;
	// 	cv::Point seond_point_line=itr->second;

	// 	// y=mx+c
	// 	//c=mx-y
	// 	int m=slope_line(first_point_line,seond_point_line);
	// 	int c=m*first_point_line.x-first_point_line.y;
	// 	// std::cout<<c<<" c of line and slope "<<slope_line<<std::endl;
	// 	line_calculated.x=first_point_line.x;
	// 	line_calculated.y=first_point_line.y;
	// 	line_calculated.c=c;
	// 	line_calculated.m=m;
	// 	// line_e_holder.push_back(line_calculated);

	// 	// std::cout<<"line start point:= "<<itr->first<<" line end point:= "<<itr->second<<std::endl;
	// }

	// for(auto itr:line_e_holder)
	// {
	// 	// std::cout<<&itr.c<<std::endl;
	// 	line_1=itr;
	// 	for(auto itr_r:line_e_holder)
	// 	{
	// 		line_2=itr_r;
	// 		// int x=


	// 	}


	// }



	// cv::rectangle(image,bounderies,Scalar(255,0,0),1,8,1);
	// if(x_cursor>bounderies.x&&y_cursor>bounderies.y && x_cursor<(bounderies.height+bounderies.x) && y_cursor< (bounderies.width+bounderies.y))
	// {
	// 	std::cout<<"inside rectangle"<<std::endl;
	// }
	imshow("Output", image);
	key_vlaue=waitKey(1);
	if(key_vlaue=='d')
	{
		draw_status=true;
	}
	if(key_vlaue=='o')
	{
		draw_status=false;
	}
	if(key_vlaue=='c')
	{
		mouse_event.clear();
		line_vector.clear();
	}
	if(key_vlaue=='a')
	{
		draw_circle=true;
	}
	if(key_vlaue=='z')
	{
		draw_circle=false;

	}
	if(key_vlaue=='s')
	{
		Mat graymat;
		cv::cvtColor(image,graymat,cv::COLOR_BGR2GRAY);
		imwrite("/home/goalbytes/_dev/opecv-line-draw/edited_map.pgm", graymat); 
		std::cout<<"image_saved"<<std::endl;
	}
	if(key_vlaue=='u')
	{
		if(mouse_event.size()>0)
		{
			mouse_event.pop_back();
			mouse_event.pop_back();
			std::cout<<"undo operation"<<std::endl;

		}
	}
	
	line_e_holder.clear();


	  auto end_time = std::chrono::high_resolution_clock::now();
	  auto time = end_time - start_time;

		std::cout <<time/std::chrono::milliseconds(1) << "ms to run.\n";
	}
	

	return 0;

}

