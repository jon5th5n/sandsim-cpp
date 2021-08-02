#include <iostream>
#include <vector>



namespace ss
{
    struct Material
    {
        // Enter density and which directions you want to check, in the order you want to check them.
        //
        // State of Aggregation has to be one of the following: "solid", "liquid", "gaseous" or "undefined" if you don't want to have any interaction.
        //
        //    Directions:
        //
        //    [4][5][6]
        //    [3][X][7]
        //    [2][1][8]
        //
        //    Enter '0' if you dont want to check anywhere.
        //
        Material(std::string name_, std::string stateOfAggregation = "undefined", float density_ = 1.0, int c1 = 0, int c2 = 0, int c3 = 0, int c4 = 0, int c5 = 0, int c6 = 0, int c7 = 0, int c8 = 0) {
            
            name = name_;
            state = stateOfAggregation;
            density = density_;

            checks[0] = c1;
            checks[1] = c2;
            checks[2] = c3;
            checks[3] = c4;
            checks[4] = c5;
            checks[5] = c6;
            checks[6] = c7;
            checks[7] = c8;
        }

        std::string name;
        std::string state;
        float density;
        int checks[8];

    
        // an array which has corresponding x-directions to the checks in the material
        int xDir[9] =
        {
            0,   // self        [0]

            0,   // below       [1]
           -1,   // left-below  [2]
           -1,   // left        [3]
           -1,   // left-above  [4]
            0,   // above       [5]
            1,   // right-above [6]
            1,   // right       [7]
            1    // right-below [8]
        };

        // an arrays which has corresponding y-directions to the checks in the material
        int yDir[9] =
        {
            0,   // self        [0]

            1,   // below       [1]
            1,   // left-below  [2]
            0,   // left        [3]
           -1,   // left-above  [4]
           -1,   // above       [5]
           -1,   // right-above [6]
            0,   // right       [7]
            1    // right-below [8]
        };
    };




    struct Grid
    {
        Grid(int width_, int height_, Material standart) {
            width = width_;
            height = height_;

            for(int i = 0; i < width * height; i++) {
                grid.push_back(standart);
            }
        }

        int width;
        int height;

        std::vector<Material> grid;



        void update() {

            // make a copy of the grid in the current state
            Grid copyGrid = *this;

            Material occupiedPlaceHolder{"occupied", "undefined"};

            // go through every cell of the grid copy
            for(int x = 0; x < copyGrid.width; x++) {
                for(int y = 0; y < copyGrid.height; y++) {

                    // get the material at the current position and just continue if it's undefined
                    Material copyMaterial = copyGrid.get(x, y);
                    if(copyMaterial.state == "undefined") continue;

                    for(int i = 0; i < 8; i++) {

                        // get the direction to check in
                        int check = copyMaterial.checks[i];
                        if(check == 0) break;

                        // get material located in the direction of the check
                        Material checkMaterial = copyGrid.get(x + copyMaterial.xDir[check], y + copyMaterial.yDir[check]);


                        //== should check for where to set the particle based on density and state etc. (currently merges multiple particle into one which corresponds into particle loss)
                        if(checkMaterial.name != "occupied" && checkMaterial.state != "solid" && copyMaterial.density > checkMaterial.density) {
                            copyGrid.set(x + copyMaterial.xDir[check], y + copyMaterial.yDir[check], occupiedPlaceHolder);
                            set(x + copyMaterial.xDir[check], y + copyMaterial.yDir[check], copyMaterial);
                            set(x, y, checkMaterial);
                            break;
                        }
                    }
                }
            }


            // for(int x = 0; x < width; x++) {
            //     for(int y = height ; y >= 0; y--) {

            //         Material selfMaterial = get(x, y);
            //         if(selfMaterial.state == "undefined") continue;

            //         int xDir[] =
            //         {
            //             x  ,   // self        [0]

            //             x  ,   // below       [1]
            //             x-1,   // left-below  [2]
            //             x-1,   // left        [3]
            //             x-1,   // left-above  [4]
            //             x  ,   // above       [5]
            //             x+1,   // right-above [6]
            //             x+1,   // right       [7]
            //             x+1    // right-below [8]
            //         };

            //         int yDir[] =
            //         {
            //             y  ,   // self        [0]

            //             y+1,   // below       [1]
            //             y+1,   // left-below  [2]
            //             y  ,   // left        [3]
            //             y-1,   // left-above  [4]
            //             y-1,   // above       [5]
            //             y-1,   // right-above [6]
            //             y  ,   // right       [7]
            //             y+1    // right-below [8]
            //         };

            //         for(int i = 0; i < 8; i++) {

            //             int check = selfMaterial.checks[i];
            //             if(check == 0) continue;

            //             Material checkedMaterial = get(xDir[check], yDir[check]);

            //             if(checkedMaterial.name == "air") {
            //                 set(xDir[check], yDir[check], selfMaterial);
            //                 set(x, y, checkedMaterial);
            //                 break;
            //             }
            //         }
            //     }
            // }
        }



        void createBorder(Material material) {
            for(int i = 0; i < width; i++) {
                set(i, 1, material);
                set(i, height-1, material);
            }
            for(int i = 0; i < height; i++) {
                set(0, i, material);
                set(width-1, i, material);
            }
        }



        // Get the index of the grid array at a given point
        int indexOf(int x, int y) const {
            return y * width + x;
        }

        // Get the x coordinate of the given index from the array
        int xOfIndex(int index) const {
            return index % width;
        }

        // Get the y coordinate of the given index from the array
        int yOfIndex(int index) const {
            return (int)(index / width);
        }

        // Get the material in the array at a given point
        Material get(int x, int y) const {
            if(x < 0 || x > width - 1 || y < 1 || y > height - 1) return Material("void", "undefined");
            return grid[indexOf(x, y)];
        }

        // Set the material in the array at a given point
        void set(int x, int y, Material material) {
            if(x < 0 || x > width - 1 || y < 1 || y > height - 1) return;
            grid[indexOf(x, y)] = material;
        }
    };
}