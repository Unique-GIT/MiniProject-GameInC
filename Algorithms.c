#include"basicWritingFunctions.c"

void drawThickLine(int x0, int y0, int x1, int y1, int thickness, short color) ;
void draw_line(int x1,int y1,int x2,int y2);
void draw_circle(int centerX,int centerY,int radius);


void draw_line(int x1, int y1, int x2, int y2) {
    int dx = abs((x2 - x1));
    int dy = abs((y2 - y1));
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (x1 != x2 || y1 != y2) {
        write_pixel(x1, y1,NAVY);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


void draw_circle(int centerX, int centerY, int radius) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        write_pixel(centerX + x, centerY + y, NAVY);
        write_pixel(centerX + y, centerY + x, NAVY);
        write_pixel(centerX - y, centerY + x, NAVY);
        write_pixel(centerX - x, centerY + y, NAVY);
        write_pixel(centerX - x, centerY - y, NAVY);
        write_pixel(centerX - y, centerY - x, NAVY);
        write_pixel(centerX + y, centerY - x, NAVY);
        write_pixel(centerX + x, centerY - y, NAVY);

        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
    return;
}

// Function to draw a thick line using Bresenham's algorithm
// Function to draw a thick line using Bresenham's algorithm
void drawThickLine(int x0, int y0, int x1, int y1, int thickness, short color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    if (dx > dy) {
        for (int i = -thickness / 2; i < thickness / 2; i++) {
            draw_line(x0, y0 + i, x1, y1 + i);
        }
    } else {
        for (int i = -thickness / 2; i < thickness / 2; i++) {
            draw_line(x0 + i, y0, x1 + i, y1);
        }
    }
}
