/*
 *  This file is part of Dune Legacy.
 *
 *  Dune Legacy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Dune Legacy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Dune Legacy.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ICNFILE_H
#define ICNFILE_H

#include <SDL.h>
#include <SDL_rwops.h>
#include <stdarg.h>
#include <vector>

/// A class for loading a *.ICN-File and the corresponding *.MAP-File.
/**
    This class can read icn-Files and return the contained pictures as a SDL_Surface. An icn-File contains
    small 16x16 pixel tiles. The map-file contains the information how to build up a complete picture with
    this small tiles.
*/
class Icnfile
{
private:
    /// Internal structure for the MAP-File.
    struct MapfileEntry
    {
        Uint32 numTiles;
        std::vector<Uint16> tileIndices;
    };

public:
    Icnfile(SDL_RWops* icnRWop, SDL_RWops* mapRWop, int freesrc);
    Icnfile(const Icnfile& o) = delete;
    ~Icnfile();


    SDL_Surface * getPicture(Uint32 IndexOfFile);
    SDL_Surface * getPictureArray(Uint32 mapfileIndex, int tilesX = 0, int tilesY = 0, int tilesN = 0);
    SDL_Surface * getPictureRow(Uint32 startIndex,Uint32 endIndex, Uint32 maxRowLength = 0);
    SDL_Surface * getPictureRow2(unsigned int numTiles, ...);

    /// Returns the number of tiles
    /**
        Returns the number of tiles in the icn-File.
        \return Number of tiles
    */
    int getNumFiles() const { return numFiles; };

    /// Returns the number of tilesets
    /**
        Returns the number of tilesets in the map-File.
        \return Number of tilesets
    */
    int getNumTilesets() const { return tilesets.size(); };

private:
    uint8_t* pIcnFiledata;
    Uint32 numFiles;

    std::vector<MapfileEntry> tilesets;

    uint8_t* SSET;
    Uint32 SSET_Length;
    uint8_t* RPAL;
    Uint32 RPAL_Length;
    uint8_t* RTBL;
    Uint32 RTBL_Length;
};

#endif // ICNFILE_H
