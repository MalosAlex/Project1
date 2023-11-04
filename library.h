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
extern GtkEntry *entry1;
extern GtkEntry *entry2;
extern GtkEntry *entry3;
extern GtkEntry *entry4;
extern GtkEntry *entry5;
extern GtkEntry *entry6;
extern GtkLabel *error1;
extern GtkLabel *error2;
extern GtkLabel *error3;
extern GtkLabel *error4;
extern GtkLabel *error5;
extern GtkLabel *error6;
extern GtkLabel *feedback;


// The data structures
struct Transaction {
    int year, month, day;
    char description[256];
    float amount;
    char type[8]; // income or expense
};

extern struct Transaction transactions[1001];
extern struct Transaction aux;
extern int numTransactions;
extern float currentAmount;

// Function prototypes
void save_transaction(const char* filename, struct Transaction transaction);
void load_transaction(const char* filename);
void insert_button_clicked(GtkButton *button, gpointer user_data);
void exit_button_clicked(GtkButton *button, gpointer user_data);
void exit_button_insert(GtkButton *button, gpointer user_data);
void exit_button_show(GtkButton *button, gpointer user_data);
void show_button_clicked(GtkButton *button, gpointer user_data);
void submit_button_clicked(GtkButton *button, gpointer user_data);
void entry_changed(GtkEntry *entry, GtkButton *submit_button);
gboolean validate_all_entries();
gboolean check_e1(GtkEntry *entry);
gboolean check_e2(GtkEntry *entry);
gboolean check_e3(GtkEntry *entry);
gboolean check_e4(GtkEntry *entry);
gboolean check_e5(GtkEntry *entry);
gboolean check_e6(GtkEntry *entry);

#endif