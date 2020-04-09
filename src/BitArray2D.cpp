//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <math.h>
#include "BitArray2D.hpp"

BitArray2D::BitArray2D(unsigned int rows, unsigned int columns) {
    if (rows <= 0)
    {
        throw BitArray2DException("row is invalid");
    }
    if (columns <= 0)
    {
        throw BitArray2DException("column is invalid");
    }
    BitArray2D::rows = rows;
    BitArray2D::columns = columns;
    BitArray2D::array = new char[rows*columns];
}


BitArray2D::~BitArray2D() {
    delete BitArray2D::array;
}


bool BitArray2D::get(unsigned int row, unsigned int column){
   // check array bounds
   if (row < 0)
   {
       throw BitArray2DException("row too low");
   }
   else if (row >= BitArray2D::rows)
   {
       throw BitArray2DException("row too high");
   }
   if (column < 0)
   {
       throw BitArray2DException("column to low");
   }
   else if (column >= BitArray2D::columns)
   {
       throw BitArray2DException("col too high");
   }

   // get the element
   return get_bit_elem(array, columns, row, column);
}



void BitArray2D::set(unsigned int row, unsigned int column){
   // check array bounds
    if (row < 0)
    {
        throw BitArray2DException("row too low");
    }
    else if (row >= BitArray2D::rows)
    {
        throw BitArray2DException("row too high");
    }
    if (column < 0)
    {
        throw BitArray2DException("column to low");
    }
    else if (column >= BitArray2D::columns)
    {
        throw BitArray2DException("col too high");
    }

    // set the element
   set_bit_elem(array, columns, row, column);
}
