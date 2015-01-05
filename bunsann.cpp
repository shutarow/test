#include<stdio.h>
#include <iostream>
using namespace std;
#include<opencv2\opencv.hpp>
using namespace cv;
#include<fstream>

int main()
{
	FILE *kiroku;
	kiroku = fopen("hyouka1sini15-15-20.csv","w");
	for(int kzn=15;kzn<=20;kzn++){
//		for(int wh = 20;wh<=35;wh+=5){
	int	wh = 15;
	double rtatz = 0,tatz=0,shogoz=0;
	double f = 1000/getTickFrequency();
	int64 time = getTickCount();
	cout << "kzn= " << kzn << "  wh=" << wh << endl;
	for(int dsc=2;dsc<=968;dsc++){

//	FILE *file;
//	FILE *fp;
	char    str[500];
//	char	str2[500];
	char fname[500];
	char fname2[500];
//	file = fopen("file.txt", "w");
//	int h = 90;
	sprintf(str,"shashin/DSC00%03d.JPG",dsc);
//	sprintf(str2,"camera/trck000002.JPG");
	Mat img = imread(str);
//	Mat img2 = imread(str2);
	Mat img2 = Mat(img.size(),CV_64FC3);
	Mat var = Mat(img.size(),CV_8UC1);
	Mat var2 = Mat(img.size(),CV_8UC3);
	Mat integ;// = Mat(img.cols+1,img.rows+1,CV_32FC1);
	Mat integ2;
	Mat hsvimg;
	double bunsan_max = 0;
	cvtColor(img,hsvimg,CV_BGR2HSV);
	uchar * data = hsvimg.data;
//	uchar * vdata2 = var2.data;
	int * data2 = img2.ptr<int>();//.ptr<double>();
	uchar * vdata = var.data;
	double re=0,gr=0,bl=0;
	Rect awaseta;
	Rect rd;
	Rect zissai[500];
	Rect zissai2[500];
	integral(hsvimg,integ);
	integral(img2,integ2);
	int * idata = integ.ptr<int>();
	double * i2data = integ2.ptr<double>();
	Rect atai[50];
	sprintf(fname,"rtat/DSC00%03d.txt",dsc);
	sprintf(fname2,"hyoukakibi/DSC00%03d.jpg",dsc);
	ifstream ifs(fname);
	string strr;
	int rtat= 0;
	int a=0,b=0;
	if(ifs.fail()){
		cerr << "File do not exist.\n";
		exit(0);
	}
	int p = 0;
	while(getline(ifs,strr)){
		sscanf(strr.data(),"%d %d",&a ,&b);
		switch((p+1)%2){
		case 1:
			atai[rtat].x = a;
			atai[rtat].y = b;
			p++;
			continue;
		default:
			atai[rtat].width = a - atai[rtat].x;
			atai[rtat].height = b - atai[rtat].y;
			rtat++,p++;
			continue;
		}}
	ifs.close();
	for(int p=0;p<=2;p++){

		i2data[3*(0)+integ.cols*(0)*3+p] = (data[3*(0)+img.cols*(0)*3+p])*(data[3*(0)+img.cols*(0)*3+p]);
	for(int x = 1;x<img.cols;x++){	
		i2data[3*(x)+integ.cols*(0)*3+p] = i2data[3*(x-1)+integ.cols*(0)*3+p] + (data[3*(x)+img.cols*(0)*3+p])*(data[3*(x)+img.cols*(0)*3+p]);
	}
	for(int y = 1;y<img.rows;y++){
		i2data[3*(0)+integ.cols*(y)*3+p] = (data[3*(0)+img.cols*(y)*3+p])*(data[3*(0)+img.cols*(y)*3+p]);
	}


	for(int y = 1;y<img.rows;y++){
			for(int x = 1;x<img.cols;x++){
				i2data[3*(x)+integ.cols*(y)*3+p] = i2data[3*(x-1)+integ.cols*(y)*3+p] + (data[3*(x)+img.cols*(y)*3+p])*(data[3*(x)+img.cols*(y)*3+p]);
					}}

	for(int y = 1;y<img.rows;y++){
		i2data[3*(0)+integ.cols*(y)*3+p] = i2data[3*(0)+integ.cols*(y-1)*3+p] + (data[3*(0)+img.cols*(y)*3+p])*(data[3*(0)+img.cols*(y)*3+p]);
	}


	
	for(int y = 1;y<img.rows;y++){
				for(int x = 1;x<img.cols;x++){
					i2data[3*(x)+integ.cols*(y)*3+p] = i2data[3*(x)+integ.cols*(y)*3+p] + i2data[3*(x)+integ.cols*(y-1)*3+p];
				}}

	}


/*	int x = 1;
	int y = 1;
	cout << "Œ³" << i2data[3*(x)+integ.cols*(y)*3+2] << endl;
	cout << "¶ã" << i2data[3*(x-1)+integ.cols*(y+1)*3+2] << endl;
	cout << "‰Eã" << i2data[3*(x+1)+integ.cols*(y+1)*3+2] << endl;
	cout << "¶‰º" << i2data[3*(x-1)+integ.cols*(y-1)*3+2] << endl;
	cout << "‰E‰º" << i2data[3*(x+1)+integ.cols*(y+1)*3+2] << endl;
*/
//		fp = fopen("fp.csv","w");
	zissai[0].x=0;
	zissai[0].y=0;
	zissai[0].width=2;
	zissai[0].height=2;
	int tat = 0;
//	int wh = 30;
	for(int y = 1; y < img.rows/2 ; y++){
		for(int x = 1; x < img.cols ; x++){
			double sqsum =0; 
			
//				sqsum += (i2data[3*(x-1+wh)+integ.cols*(y-1+wh)*3+2]-i2data[3*(x-1)+integ.cols*(y-1+wh)*3+2]-i2data[3*(x-1+wh)+integ.cols*(y-1)*3+2]+i2data[3*(x-1)+integ.cols*(y-1)*3+2])/(wh*wh) - ((idata[3*(x+wh)+integ.cols*(y+wh)*3+2]-idata[3*(x)+integ.cols*(y+wh)*3+2]-idata[3*(x+wh)+integ.cols*(y)*3+2]+idata[3*(x)+integ.cols*(y)*3+2])/(wh*wh))*((idata[3*(x+wh)+integ.cols*(y+wh)*3+2]-idata[3*(x)+integ.cols*(y+wh)*3+2]-idata[3*(x+wh)+integ.cols*(y)*3+2]+idata[3*(x)+integ.cols*(y)*3+2])/(wh*wh));
//				sqsum += (i2data[3*(x-1+wh)+integ.cols*(y-1+wh)*3+1]-i2data[3*(x-1)+integ.cols*(y-1+wh)*3+1]-i2data[3*(x-1+wh)+integ.cols*(y-1)*3+1]+i2data[3*(x-1)+integ.cols*(y-1)*3+1])/(wh*wh) - ((idata[3*(x+wh)+integ.cols*(y+wh)*3+1]-idata[3*(x)+integ.cols*(y+wh)*3+1]-idata[3*(x+wh)+integ.cols*(y)*3+1]+idata[3*(x)+integ.cols*(y)*3+1])/(wh*wh))*((idata[3*(x+wh)+integ.cols*(y+wh)*3+1]-idata[3*(x)+integ.cols*(y+wh)*3+1]-idata[3*(x+wh)+integ.cols*(y)*3+1]+idata[3*(x)+integ.cols*(y)*3+1])/(wh*wh));
				sqsum += (i2data[3*(x-1+wh)+integ.cols*(y-1+wh)*3]-i2data[3*(x-1)+integ.cols*(y-1+wh)*3]-i2data[3*(x-1+wh)+integ.cols*(y-1)*3]+i2data[3*(x-1)+integ.cols*(y-1)*3])/(wh*wh) - ((idata[3*(x+wh)+integ.cols*(y+wh)*3]-idata[3*(x)+integ.cols*(y+wh)*3]-idata[3*(x+wh)+integ.cols*(y)*3]+idata[3*(x)+integ.cols*(y)*3])/(wh*wh))*((idata[3*(x+wh)+integ.cols*(y+wh)*3]-idata[3*(x)+integ.cols*(y+wh)*3]-idata[3*(x+wh)+integ.cols*(y)*3]+idata[3*(x)+integ.cols*(y)*3])/(wh*wh));
		
//		sqsum = (sqsum/3)*2;
		sqsum = sqrt( sqsum/ (double)2 );
		sqsum = sqsum*2;

//				fprintf(fp,"%f,",sqsum);
			

//		cout << sqsum << endl;
//		sqsum = sqsum*2;
//		vdata[ x + y * var.cols] = sqsum;

		
		if (sqsum > kzn){
			rd.x = x;
			rd.y = y;
			rd.width = wh;
			rd.height = wh;
			
		for(int i = 0;i<=tat;i++){
			awaseta = rd & zissai[i];
			if(awaseta.area() != 0){
				zissai[i] = rd | zissai[i];
				break;
				}
			if(i == tat){
			tat++;
			zissai[tat] = rd;
			}}}
	
		}
//		fprintf(fp,"\n");	
	}

//	fclose(fp);



	Rect bou;
	bou.x = 2300;
	bou.y = 1300;
	bou.height = 500;
	bou.width = 300;
	for(int l=0;l<=5;l++){
	for(int x=0;x<=tat;x++){
	bool tl = bou.contains(zissai[x].tl());
	bool br = bou.contains(zissai[x].br());	
	if(tl == true || br == true){
		for(int k=x;k<=tat-1;k++){
			zissai[k] = zissai[k+1];
		}
		tat--;
	}}}

//	cout << "”Ô†" << dsc << endl;

//	cout << "ŽÀÛ‚Ì”" << rtat << endl;

	for(int l=0;l<=10;l++){
	for(int x=0;x<=tat;x++){
		for(int y=0;y<=tat;y++){
			if(x != y){
	bool tl = zissai[x].contains(zissai[y].tl());
	bool br = zissai[x].contains(zissai[y].br());	
	if(tl == true || br == true){
		for(int k=y;k<=tat-1;k++){
			zissai[k] = zissai[k+1];
		}
		tat--;
	}}}}}

//	cout << "ŒvŽZ‚µ‚½”" << tat << endl;

	int shogo = 0;
	int tatr = 0;
	for(int m=0;m<=rtat;m++){
		for(int n=0;n<=tat;n++){
			awaseta = atai[m] & zissai[n];
			if(awaseta.area() > atai[m].area()/2 && (zissai[n].area() - awaseta.area()) < awaseta.area()*0.5 ){
				zissai2[tatr] = zissai[n];
				shogo++;
				break;;
			}
		}}
	tatz += tat;
	shogoz += shogo;
	rtatz += rtat;
/*
//	cout << "‚ ‚½‚Á‚½”" << shogo << endl;

	for(int i=0;i<=tat;i++){
	Point p0;
	p0=zissai[i].tl();
	Point p1;
	p1=zissai[i].br();
	rectangle(img,p0,p1,Scalar(0,0,0255));
//	printf("%d %d \n",zissai[i].x,zissai[i].y);
	}
	
	for(int i=0;i<=rtat;i++){
	Point p0;
	p0=atai[i].tl();
	Point p1;
	p1=atai[i].br();
	rectangle(img,p0,p1,Scalar(0,0,0));
//	printf("%d %d \n",zissai[i].x,zissai[i].y);
	}

	for(int i=0;i<=tatr;i++){
	Point p0;
	p0=zissai2[i].tl();
	Point p1;
	p1=zissai2[i].br();
	rectangle(img,p0,p1,Scalar(0,255,0));
//	printf("%d %d \n",zissai[i].x,zissai[i].y);
*/
	}
	
//	namedWindow("trck");
//	namedWindow("var");
//	imshow("trck", img);
//	imwrite(fname2,img);
//	imshow("var", var);
//	destroyWindow("trck");
//	destroyWindow("var");
	double zikan = (getTickCount()-time)*f;
//	cout << "time " << (getTickCount()-time)*f << "[ms]" <<endl;
	double kensyutu = shogoz / rtatz;
	double gokensyutu = (tatz - shogoz)/tatz;
	fprintf(kiroku,"%d,%d,%f,%f,%f,%f,%f,%f",kzn,wh,tatz,rtatz,shogoz,kensyutu,gokensyutu,zikan);
	fprintf(kiroku,"\n");

	}	
	
	fclose(kiroku);
}
