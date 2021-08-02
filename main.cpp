#include <iostream>

#include "raylib.h"
#include "C:/raylib/raylib/src/raymath.h"

#include "sandsim.cpp"


using namespace std;



void selectBrushAndDraw(ss::Grid* grid, int scale, std::vector<ss::Material> drawMaterials, ss::Material eraseMaterial, int* selectedMaterialIndex, int* brushSize);
void drawGrid(ss::Grid, int scale);



int main(int argc, char const *argv[]) //========
{
    int width = 300;     
    int height = 200;

    int screenScale = 3;
    int screenWidth = width * screenScale;
    int screenHeight = height * screenScale;
    
    ss::Material air{"air", "undefined", 0.0};
    ss::Material stone{"stone", "solid"};
    ss::Material sand{"sand", "solid", 5.0, 1, 2, 8};
    ss::Material water{"water", "fluid", 2.0, 1, 2, 8, 3, 7};
    ss::Material N2O{"N2O", "gaseous", 0.2, 5, 4, 6, 3, 7};

    ss::Grid grid{width, height, air};
    grid.createBorder(stone); 

    int selectedMaterialIndex = 0;
    int brushSize = 5;


    InitWindow(screenWidth, screenHeight, "Sand Simulation");
    SetTargetFPS(60);

    while(!WindowShouldClose()) //===============
    {
        grid.update();

        selectBrushAndDraw(&grid, screenScale, std::vector<ss::Material>{stone, sand, water, N2O}, air, &selectedMaterialIndex, &brushSize);


        BeginDrawing(); //=======================

        ClearBackground(WHITE);
        DrawFPS(screenWidth - 85, 5);

        if(!IsKeyDown(32))
            drawGrid(grid, screenScale);


        EndDrawing(); //=========================
    }

    return 0;           
}




void selectBrushAndDraw(ss::Grid* grid, int scale, std::vector<ss::Material> drawMaterials, ss::Material eraseMaterial, int* selectedMaterialIndex, int* brushSize) {

    auto draw = [=](int x, int y, int size, ss::Material material) {
        for(int w = -size; w <= size; w++) {
            for(int h = -size; h <= size; h++) {
                grid->set((x/scale) + w, (y/scale) + h, material);
            }
        }
    };



    if(GetMouseWheelMove() > 0) {
        if(IsKeyDown(83)) *brushSize += 1;
        else *selectedMaterialIndex += 1;
    }
    else if(GetMouseWheelMove() < 0) {
        if(IsKeyDown(83) && *brushSize > 0) *brushSize -= 1;
        else if(!IsKeyDown(83)) *selectedMaterialIndex -= 1;
    }


    if(*selectedMaterialIndex < 0) *selectedMaterialIndex = drawMaterials.size() - 1;
    *selectedMaterialIndex = *selectedMaterialIndex % drawMaterials.size();

    ss::Material selectedMaterial = drawMaterials[*selectedMaterialIndex];


    if(IsMouseButtonDown(0)) {
        draw(GetMouseX(), GetMouseY(), *brushSize, selectedMaterial);
    }
    else if(IsMouseButtonDown(1)) {
        draw(GetMouseX(), GetMouseY(), *brushSize, eraseMaterial);
    }

    if(IsKeyPressed(KEY_ENTER)) {
        for(int x = 0; x < grid->width; x++) {
            for(int y = 0; y < grid->height; y++) {
                grid->set(x, y, eraseMaterial);
            }
        }
        grid->createBorder(drawMaterials[0]); 
    }


    DrawText(&*selectedMaterial.name.begin(), 5, 5, 20, RED);
    DrawText((std::to_string(*brushSize)).c_str(), 5, 25, 18, RED);
}



void drawGrid(ss::Grid grid, int scale) {

    auto drawToScale = [=](int x, int y, Color color) {
        if(scale != 1) {
            for(int w = 0; w < scale; w++) {
                for(int h = 0; h < scale; h++) {
                    DrawPixel((x * scale) + w, (y * scale) + h, color);
                }
            }
            return;
        }

        DrawPixel(x, y, color);
    };

    for(int x = 0; x < grid.width; x++) {
        for(int y = 0; y < grid.height; y++) {
            if(grid.get(x, y).name == "stone") {
                drawToScale(x, y, GRAY);
            }
            else if(grid.get(x, y).name == "sand") {
                drawToScale(x, y, GOLD);
            }
            else if(grid.get(x, y).name == "water") {
                drawToScale(x, y, SKYBLUE);
            }
            else if(grid.get(x, y).name == "N2O") {
                drawToScale(x, y, (Color){200, 200, 200, 150});
            }
        }
    }
}










