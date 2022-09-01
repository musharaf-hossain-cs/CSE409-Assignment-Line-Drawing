#include<bits/stdc++.h>
#include "bitmap_image.hpp"
using namespace std;

int height = 100;
int width = 100;

struct Color {
    int r;
    int g;
    int b;
    Color(){
        r=g=b=0;
    }
    Color(int r, int g, int b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

struct Line{
    int startx;
    int starty;
    int endx;
    int endy;
    Color color;

    Line(){
        startx = starty = endx = endy = 0;
    }

    Line(int sx, int sy, int ex, int ey, Color color=Color()){
        startx = sx;
        starty = sy;
        endx = ex;
        endy = ey;
        this->color = color;
    }
    void Print(){
        cout<<"("<<startx<<","<<starty<<") ==> ("<<endx<<","<<endy<<")"<<endl;
    }
};


vector<Line> lines;

void MidPointLine() {
    bitmap_image image(width, height);
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            image.set_pixel(i, j, 255, 255, 255);
        }
    }

    for(Line line : lines){
        line.Print();
        int dx = line.endx - line.startx;
        int dy = line.endy - line.starty;

        // x axis or parallel to x-axis
        if(line.starty == line.endy){
            int x = line.startx;
            if(x < 0) x = 0;
            int xLimit = min(line.endx, width);
            if(line.starty >= 0 && line.starty < height){
                while(x < xLimit){
                    image.set_pixel(x, line.starty, line.color.r, line.color.g, line.color.b);
                    x++;
                }
            }
        }
        // y axis or parallel to y-axis
        else if(line.startx == line.endx){
            int y = min(line.starty, line.endy);
            if(y < 0) y = 0;
            int yLimit = min(max(line.endy, line.starty), height);
            if(line.startx >= 0 && line.startx < width){
                while(y < yLimit){
                    image.set_pixel(line.startx, y, line.color.r, line.color.g, line.color.b);
                    y++;
                }
            }

        }
        // when absolute value of slope m <= 1
        else if(abs((double)dy/dx) <= 1){
            int x = line.startx;
            int y = line.starty;
            if(x < 0){
                int diffx = -x;
                x = 0;
                y = y + (int) ( ((double)dy/dx) * diffx );
            }

            if(dy < 0) dy = -dy;
            int d = 2 * dy - dx;
            int eIncrement = 2 * dy;
            int neIncrement = 2 * (dy - dx);

            int ydir = line.endy >= line.starty ? 1 : -1;
            int xLimit = min(width, line.endx);

            while ( x < xLimit) {
                image.set_pixel(x, y, line.color.r, line.color.g, line.color.b);

                if(d <= 0){
                    d += eIncrement;
                }
                else {
                    d += neIncrement;
                    y += ydir;
                }
                x++;
            }
        }

        // when absolute value of slope m > 1
        else if(abs((double)dy/dx) > 1){
            if(line.starty > line.endy){
                // point swap
                swap(line.starty, line.endy);
                swap(line.startx, line.endx);
            }

            int x = line.startx;
            int y = line.starty;
            if(y < 0){
                int diffy = -y;
                y = 0;
                x = x + (int) ( ((double)dx/dy) * diffy );
            }

            if(dx < 0) dx = -dx;
            int d = 2 * dx - dy;
            int eIncrement = 2 * dx;
            int neIncrement = 2 * (dx - dy);

            int xdir = line.endx >= line.startx ? 1 : -1;
            int yLimit = min(height, line.endy);

            while ( y < yLimit) {
                image.set_pixel(x, y, line.color.r, line.color.g, line.color.b);

                if(d <= 0){
                    d += eIncrement;
                }
                else {
                    d += neIncrement;
                    x += xdir;
                }
                y++;
            }
        }

    }
    image.save_image("MidpointLine.bmp");
}

void LoadScene(){
    ifstream input;
    input.open("input.txt");
    if(!input){
        cout<<"error in opening file"<<endl;
        return;
    }
    input >> width >> height;

    int n;

    input >> n;
    int sx, sy, ex, ey;
    Color color;

    while(n--){
        input >> sx >> sy >> ex >> ey;
        input >> color.r >> color.g >> color.b;
        if( sx <= ex){
            lines.push_back(Line(sx, sy, ex, ey, color));
        }
        else {
            lines.push_back(Line(ex, ey, sx, sy, color));
        }

    }
}

int main(){
    cout<<"Started"<<endl;
    LoadScene();
    MidPointLine();
}
