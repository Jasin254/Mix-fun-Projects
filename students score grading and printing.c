#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "itext.h"

int main() {
    // Collect student scores
    float scores[8];
    printf("Enter the scores for 8 subjects:\n");
    for (int i = 0; i < 8; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &scores[i]);
    }

    // Calculate the average
    float sum = 0;
    for (int i = 0; i < 8; i++) {
        sum += scores[i];
    }
    float average = sum / 8;

    // Grade students
    char grade[3];
    if (average >= 90) {
        strcpy(grade, "A+");
    } else if (average >= 80) {
        strcpy(grade, "A");
    } else if (average >= 70) {
        strcpy(grade, "B");
    } else if (average >= 60) {
        strcpy(grade, "C");
    } else {
        strcpy(grade, "F");
    }

    // Create a PDF report
    char filename[100];
    sprintf(filename, "student_report_%d.pdf", rand()); // Random filename to avoid overwriting
    create_pdf(filename, scores, average, grade);

    printf("Student report generated successfully!\n");
    return 0;
}

void create_pdf(char* filename, float scores[], float average, char* grade) {
    itext_init();

    pdf_doc* doc = pdf_create_doc(filename);

    pdf_append_page(doc);

    pdf_set_font(doc, "Arial", 16);
    pdf_set_text(doc, "Student Report\n");
    pdf_set_text(doc, "----------------\n");

    pdf_set_text(doc, "Scores:\n");
    for (int i = 0; i < 8; i++) {
        char score_str[10];
        sprintf(score_str, "%.2f\n", scores[i]);
        pdf_set_text(doc, score_str);
    }

    char average_str[50];
    sprintf(average_str, "Average: %.2f\n", average);
    pdf_set_text(doc, average_str);

    char grade_str[50];
    sprintf(grade_str, "Grade: %s\n", grade);
    pdf_set_text(doc, grade_str);

    pdf_close(doc);

    itext_end();
}
