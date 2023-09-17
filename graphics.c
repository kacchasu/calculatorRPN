#include "graphics.h"
#include <stdio.h>
#include <math.h>

extern double evaluatePolishNotation(char **polishTokens, double x);

void drawGraph(char **tokens) {
    int rows = 25;
    int cols = 80;
    char canvas[rows][cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            canvas[i][j] = '.';
        }
    }
    double xScale = (4 * M_PI) / cols;
    double yScale = 2.0 / (rows - 1);
    for (int j = 0; j < cols; ++j) {
        double xValue = j * xScale;
        double yValue = evaluatePolishNotation(tokens, xValue);
        if (yValue < -1.0 || yValue > 1.0) {
            continue;
        }
        int rowIndex = (int) round(12 - (yValue / yScale));
        if (rowIndex >= 0 && rowIndex < rows) {
            canvas[rowIndex][j] = '*';
        }
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%c", canvas[i][j]);
        }
        if(i < rows - 1) printf("\n");
    }
}