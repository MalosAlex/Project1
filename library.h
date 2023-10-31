#ifndef DATA_H
#define DATA_H
#include <gtk/gtk.h>

// Declare global window pointers
extern GtkWindow *main_window;
extern GtkWindow *show_popup;
extern GtkWindow *insert_popup;

// Declare other global widgets
extern GtkTextView *textview;
extern GtkTextBuffer *text_buffer;

// The data structures
struct Transaction {
    int year, month, day;
    char description[256];
    float amount;
    char type[8]; // income or expense
};

extern struct Transaction transactions[1001];
extern int numTransactions;

// Function prototypes
void save_transaction(const char* filename, struct Transaction transaction);
void load_transaction(const char* filename);
void insert_button_clicked(GtkButton *button, gpointer user_data);
void exit_button_clicked(GtkButton *button, gpointer user_data);
void exit_button_insert(GtkButton *button, gpointer user_data);
void exit_button_show(GtkButton *button, gpointer user_data);
void show_button_clicked(GtkButton *button, gpointer user_data);
void submit_button_clicked(GtkButton *button, gpointer user_data);

#endif
