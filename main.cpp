/*
 * test.cpp
 *
 *  Created on: 25 Oct 2015
 *      Author: michaelbrookes
 */

#include "include/BBBLSM303DLHC.h"

int main ( void ) {

    BBBLSM303DLHC LSM303;
    LSM303.StartRecordingPitchAndRoll( );
    LSM303.StartRecordingHeading( );
    LSM303.SetPitchAndRollAverages( 500 );

    while( 1 ) {
        /*
        cout << "Heading = " << LSM303.Heading;
        cout << " | Roll = " << LSM303.Roll;
        cout << " | Pitch = " << LSM303.Pitch << endl;
        cout << "Average Heading = " << LSM303.avgHeading;
        cout << " | Average Roll = " << LSM303.avgRoll;
        cout << " | Average Pitch = " << LSM303.avgPitch << endl;
        */
        for( int i = 0; i < MAX_DATASTORE; i++ ) {
            //cout << "Pitch Stored Val " << i << " : " << LSM303.PitchDataStoredValues[ i ] << endl;
            //cout << "Roll Stored Val " << i << " : " << LSM303.RollDataStoredValues[ i ] << endl;
        }
        sleep( 1 );
    }
}
