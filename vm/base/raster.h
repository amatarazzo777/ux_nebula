/*
 * raster.hpp
 *
 *  Created on: Nov 7, 2023
 *      Author: anthonym
 */

#ifndef RASTER_HPP_
#define RASTER_HPP_

class raster_t {
public:
	/*
	 * raster.cpp
	 *
	 *  Created on: Nov 7, 2023
	 *      Author: anthonym
	 *
	 * @description The catchiness of the long way verses the short way
	 * tends to lend itself in dual fashion here. The modular math used here
	 * for stepping, and other advanced uses are very keen. One has to learn these
	 * concepts. The book that Zingl Alois published introduces the subject and building
	 * block material nicely.
	 *
	 * These routines are adopted to the ready platform use. I choose two types of buffer output
	 * in form, a font glymph blending instruction bitmap or the all time platform favorite RGBA platform.
	 *
	 */

	/********************************************************************
	*                                                                   *
	*                    Curve Rasterizing Algorithm                    *
	*                                                                   *
	********************************************************************/

	/**
	 * @author Zingl Alois
	 * @date 22.08.2016
	 * @version 1.2
	*/

	void setPixel(int x0, int y0);
	void getPixel(int x0, int y0);
	void plotLine(int x0, int y0, int x1, int y1);
	void plotEllipse(int xm, int ym, int a, int b);
	void plotOptimizedEllipse(int xm, int ym, int a, int b);
	void plotCircle(int xm, int ym, int r);
	void plotEllipseRect(int x0, int y0, int x1, int y1);
	void plotQuadBezierSeg(int x0, int y0, int x1, int y1, int x2, int y2);
	void plotQuadBezier(int x0, int y0, int x1, int y1, int x2, int y2);
	void plotQuadRationalBezierSeg(int x0, int y0, int x1, int y1,
	                               int x2, int y2, float w);
	void plotQuadRationalBezier(int x0, int y0, int x1, int y1,
	                            int x2, int y2, float w);
	void plotRotatedEllipse(int x, int y, int a, int b, float angle);
	void plotRotatedEllipseRect(int x0, int y0, int x1, int y1, long zd);
	void plotCubicBezierSeg(int x0, int y0, float x1, float y1,
	                        float x2, float y2, int x3, int y3);
	void plotCubicBezier(int x0, int y0, int x1, int y1,
	                     int x2, int y2, int x3, int y3);
	void plotLineAA(int x0, int y0, int x1, int y1);
	void plotCircleAA(int xm, int ym, int r);
	void plotEllipseRectAA(int x0, int y0, int x1, int y1);
	void plotQuadBezierSegAA(int x0, int y0, int x1, int y1, int x2, int y2);
	void plotQuadRationalBezierSegAA(int x0, int y0, int x1, int y1,
	                                 int x2, int y2, float w);
	void plotCubicBezierSegAA(int x0, int y0, float x1, float y1,
	                          float x2, float y2, int x3, int y3);
	void plotLineWidth(int x0, int y0, int x1, int y1, float wd);
	void plotQuadSpline(int n, int x[], int y[]);
	void plotCubicSpline(int n, int x[], int y[]);




};



#endif /* RASTER_HPP_ */
