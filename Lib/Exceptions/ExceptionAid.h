/*
Copyright (C) 2016 Michael Brookes

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef I2C_EXCEPTION_AID_H
#define I2C_EXCEPTION_AID_H

#include <exception>
#include <iostream>
#include <string>

namespace abI2C {
    using namespace std;

    class I2CSetupException : public exception {
    public:
        I2CSetupException( string errMessage ):errMessage_(errMessage){}
        const char* what() const throw() { return errMessage_.c_str( ); }

    private:
        string errMessage_;
    };
}

#endif //I2C_EXCEPTION_AID_H
