#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

//  THE FOLLOWING 3 LINES ARE REQUIRED TO GET ACCESS TO  M_PI  UNDER Linux
#if     defined(__linux__)
#define __USE_XOPEN
#endif

#include <math.h>

//  written by Chris.McDonald@uwa.edu.au
//
//  compile:  cc -std=c11 -Wall -Werror -o haversine2 haversine2.c -lm
//  run:      ./haversine2 lat1 lon1 lat2 lon2 [lat3 lon3 ...]
//  e.g.      ./haversine2 -31.977537 115.816451 -31.977632 115.816871 \
//                      -31.977616 115.817170 -31.980981 115.817174 \
//                      -31.980975 115.818709 -31.982842 115.818725

#define EARTH_RADIUS_IN_METRES          6372797

#define MIN_LAT             -90.0
#define MAX_LAT              90.0
#define MIN_LON             -180.0
#define MAX_LON              180.0

struct point {
    double      lat;
    double      lon;
};

double degrees_to_radians(double degrees)
{
    return (degrees * M_PI / 180.0);
}

bool valid_location(struct point location)
{
    if(location.lat  >= MIN_LAT && location.lat <= MAX_LAT   &&
       location.lon  >= MIN_LON && location.lon <= MAX_LON) {
        return true;
    }
    printf("location %f,%f is invalid!\n", location.lat, location.lon);
    return false;
}

double haversine(struct point location1, struct point location2)
{
    double deltalat = (location2.lat - location1.lat) / 2.0;
    double deltalon = (location2.lon - location1.lon) / 2.0;

    double sin1     = sin( degrees_to_radians(deltalat) );

    double cos1     = cos( degrees_to_radians(location1.lat) );
    double cos2     = cos( degrees_to_radians(location2.lat) );

    double sin2     = sin( degrees_to_radians(deltalon) );

    double x        = sin1*sin1 + cos1*cos2 * sin2*sin2;

    return (2.0 * EARTH_RADIUS_IN_METRES * asin( sqrt(x) ) );  // in metres
}

int main(int argc, char *argv[])
{
    int result  = EXIT_FAILURE;

    if(argc == 1 || ((argc - 1) % 2) != 0) {
        printf("Usage: %s lat1 lon1 lat2 lon2 [lat3 lon3 ...]\n", argv[0]);
        return result;
    }

    int             npoints = (argc-1)/2;
    struct point    location[npoints];

    int a   = 1; // index of args

    for(int p=0 ; p<npoints ; ++p) {
        location[p].lat = atof(argv[a+0]);
        location[p].lon = atof(argv[a+1]);

        if(!valid_location(location[p])) {
            npoints = 0;
            break;
        }
        a   += 2;
    }

    if(npoints > 0) {
        double distance    = 0.0;
        for(int p=0 ; p<(npoints-1) ; ++p) {
            distance    += haversine(location[p], location[p+1]);
        }
        printf("haversine distance = %im\n", (int)distance);
        result = EXIT_SUCCESS;
    }
    return result;
}
