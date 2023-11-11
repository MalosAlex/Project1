#ifndef DATA_H
#define DATA_H
#include <gtk/gtk.h>

// Declare global window pointers
extern GtkWindow *main_window;
extern GtkWindow *show_popup;
extern GtkWindow *insert_popup;
extern GtkWindow *period_popup;
extern GtkDialog *balance_dialog;


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
extern GtkEntry *pentry1;
extern GtkEntry *pentry2;
extern GtkEntry *pentry3;
extern GtkEntry *pentry4;
extern GtkEntry *pentry5;
extern GtkEntry *pentry6;
extern GtkLabel *perror1;
extern GtkLabel *perror2;
extern GtkLabel *perror3;
extern GtkLabel *perror4;
extern GtkLabel *perror5;
extern GtkLabel *perror6;
extern GtkLabel *balance_label;


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
void entry_changed_period(GtkEntry *entry, GtkButton *submit_button);
void period_submit_button_clicked(GtkButton *button, gpointer user_data);
void period_exit_button_clicked(GtkButton *button, gpointer user_data);
void period_button_clicked(GtkButton *button, gpointer user_data);
void balance_button_clicked(GtkButton *button, gpointer user_data);
void balance_exit_button_clicked(GtkButton *button, gpointer user_data);
gboolean validate_all_entries();
gboolean check_e1(GtkEntry *entry);
gboolean check_e2(GtkEntry *entry);
gboolean check_e3(GtkEntry *entry);
gboolean check_e4(GtkEntry *entry);
gboolean check_e5(GtkEntry *entry);
gboolean check_e6(GtkEntry *entry);
gboolean check_pe1(GtkEntry *entry, GtkLabel *perror1);
gboolean check_pe2(GtkEntry *entry, GtkLabel *perror2);
gboolean check_pe3(GtkEntry *entry, GtkLabel *perror3);
gboolean validate_all_entries_period();

void clear_text_view(GtkWidget *widget, gpointer data);
void clear_entry(GtkWidget *widget, gpointer data);
#endif