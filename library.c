#include <stdio.h>
#include <gtk/gtk.h>
#include "library.h"
//The functions for storing and working with data

GtkEntry *entry1;
GtkEntry *entry2;
GtkEntry *entry3;
GtkEntry *entry4;
GtkEntry *entry5;
GtkEntry *entry6;
GtkLabel *error1;
GtkLabel *error2;
GtkLabel *error3;
GtkLabel *error4;
GtkLabel *error5;
GtkLabel *error6;
GtkLabel *feedback;
GtkWindow *main_window;
GtkWindow *show_popup;
GtkWindow *insert_popup;
GtkTextView *textview;
GtkTextBuffer *text_buffer;
struct Transaction transactions[1001];
int numTransactions = 0;

struct Transaction aux;
void save_transaction(const char* filename, struct Transaction transaction)
{
    FILE* file = fopen(filename, "a"); 
    //We append the current Transaction, which we made sure is good, to the end of the file,
    // so instead of writing all the data again from the start to the end we just append the new data, thus saving time
    if(file)
    {
        fprintf(file, "%d %d %d %s %f %s\n", transaction.year, transaction.month, transaction.day, transaction.description, transaction.amount, transaction.type);
    }
    transactions[numTransactions] = transaction;
    numTransactions++;
    fclose(file);
}
void load_transaction(const char* filename)
{
    FILE* file = fopen(filename, "r"); //read
    if(file)
    {
        while(numTransactions < 1001 && fscanf(file, "%d %d %d %256[^:0-9] %f %7s\n", &transactions[numTransactions].year, &transactions[numTransactions].month,
                &transactions[numTransactions].day, transactions[numTransactions].description, &transactions[numTransactions].amount,
                transactions[numTransactions].type) == 6) //checks if it reads a value for every variable
            numTransactions = numTransactions + 1;
        fclose(file);
    }
    else
        g_print("Failed to open the file :/");
}
void entry_changed(GtkEntry *entry, GtkButton *submit_button)
{
    //we check all entries to be valid
    gboolean all_entries_valid = validate_all_entries();
    //We either enable or disable the submit button based on the valability
    gtk_widget_set_sensitive(GTK_WIDGET(submit_button), all_entries_valid);
}
gboolean validate_all_entries()
{
    gboolean e1 = check_e1(entry1);
    gboolean e2 = check_e2(entry2);
    gboolean e3 = check_e3(entry3);
    gboolean e4 = check_e4(entry4);
    gboolean e5 = check_e5(entry5);
    gboolean e6 = check_e6(entry6);
    if (e1 == FALSE || e2 == FALSE || e3 == FALSE || e4 == FALSE || e5 == FALSE || e6 == FALSE)
        return FALSE; 
    return TRUE;

}
//The functions for the buttons
void insert_button_clicked(GtkButton *button, gpointer user_data)
{
    gtk_widget_hide(GTK_WIDGET(main_window));
    gtk_widget_show_all(GTK_WIDGET(insert_popup));

    g_print("Insert button clicked!");
}
void exit_button_clicked(GtkButton *button, gpointer user_data)
{
    gtk_main_quit();
    g_print("The program was terminated successfully!");
}
void exit_button_insert(GtkButton *button, gpointer user_data)
{
    gtk_widget_hide(GTK_WIDGET(insert_popup));
    gtk_widget_show_all(GTK_WIDGET(main_window));
}
void exit_button_show(GtkButton *button, gpointer user_data)
{
    gtk_widget_hide(GTK_WIDGET(show_popup));
    gtk_widget_show_all(GTK_WIDGET(main_window));
}
void show_button_clicked(GtkButton *button, gpointer user_data)
{
    gtk_widget_hide(GTK_WIDGET(main_window));
    gtk_widget_show_all(GTK_WIDGET(show_popup));
    gtk_text_buffer_set_text(text_buffer, "", -1);  //Clearing the buffer
    for(int i = 0; i < numTransactions; i++)
    {
        char TransactionData[512];
        sprintf(TransactionData, "Date: %d/%d/%d, Description: %s, Amount: %f, Type: %s\n", transactions[i].day, transactions[i].month, transactions[i].year,
                transactions[i].description, transactions[i].amount, transactions[i].type);

        //We get the text buffer
        GtkTextBuffer *local_text_buffer = gtk_text_view_get_buffer(textview);

        //Append the transaction data to the text buffer
        gtk_text_buffer_insert_at_cursor(local_text_buffer, TransactionData, -1);
    }
}
void submit_button_clicked(GtkButton *button, gpointer user_data)
{
    //We save the transaction
    save_transaction("data_storage.txt", aux);
    g_print("Submit button clicked!");
}
gboolean check_e1(GtkEntry *entry)
{
    const gchar *text = gtk_entry_get_text(entry); //gtk_entry_get_text returns a pointer to a string
    int number = atoi(text); //converts to int
    if(number > 2023 || number < 1960)
    {
        gtk_label_set_text(error1, "Please enter a valid year, between 1960 and the current one");
        return FALSE;
    }
    gtk_label_set_markup(GTK_LABEL(error1), "<span font_desc='30'><b>✔</b></span>");
    aux.year = number;
    return TRUE;

}
gboolean check_e2(GtkEntry *entry)
{
    const gchar *text = gtk_entry_get_text(entry); //gtk_entry_get_text returns a pointer to a string
    int number = atoi(text); //converts to int
    if(number > 12 || number < 1)
    {
        gtk_label_set_text(error2, "Please enter a valid month, in a numerical value");
        return FALSE;
    }
    gtk_label_set_markup(GTK_LABEL(error2), "<span font_desc='30'><b>✔</b></span>");
    aux.month = number;
    return TRUE;

}
gboolean check_e3(GtkEntry *entry)
{
    const gchar *text = gtk_entry_get_text(entry); //gtk_entry_get_text returns a pointer to a string
    int number = atoi(text); //converts to int
    if(aux.year % 4 == 0 && aux.month == 2)
        if(number < 1 || number > 29)
        {
            gtk_label_set_text(error3, "Please enter a valid day");
            return FALSE;
        }
    else
    {
        if(aux.month == 2)
            if(number < 1 || number > 28)
            {
                gtk_label_set_text(error3, "Please enter a valid day");
                return FALSE;
            }
        if(aux.month == 1 || aux.month == 3 || aux.month == 5 || aux.month == 7 || aux.month == 8 || aux.month == 10 || aux.month == 12)
        {
            if(number < 1 || number > 31)
            {
                gtk_label_set_text(error3, "Please enter a valid day");
                return FALSE;
            }
        }
        else
        {
            if(number < 1 || number > 30)
            {
                gtk_label_set_text(error3, "Please enter a valid day");
                return FALSE;
            }
        }
    }
    gtk_label_set_markup(GTK_LABEL(error3), "<span font_desc='30'><b>✔</b></span>");
    aux.day = number;
    return TRUE;
}
gboolean check_e4(GtkEntry *entry)
{
    const gchar *text = gtk_entry_get_text(entry); //gtk_entry_get_text returns a pointer to a string
    int size = strlen(text);
    if(size < 1 || size > 256)
    {
        gtk_label_set_text(error4, "Please enter a shorter description");
        return FALSE;
    }
    gtk_label_set_markup(GTK_LABEL(error4), "<span font_desc='30'><b>✔</b></span>");
    strcpy(aux.description, text);
    return TRUE;
}
gboolean check_e5(GtkEntry *entry)
{
    const gchar *text = gtk_entry_get_text(entry); //gtk_entry_get_text returns a pointer to a string
    float number = atof(text); //converts to float
    if(number < 0)
    {
        gtk_label_set_text(error5, "Please enter a positive value");
        return FALSE;
    }
    gtk_label_set_markup(GTK_LABEL(error5), "<span font_desc='30'><b>✔</b></span>");
    aux.amount = number;
    return TRUE;
}
gboolean check_e6(GtkEntry *entry)
{
    const gchar *text = gtk_entry_get_text(entry); //gtk_entry_get_text returns a pointer to a string
    if(strcmp(text,"income") == 0 || strcmp(text,"expense") == 0)
    {
        gtk_label_set_markup(GTK_LABEL(error6), "<span font_desc='30'><b>✔</b></span>");
        strcpy(aux.type,text);
        return TRUE;
    }
    gtk_label_set_text(error6, "Please enter a valid type (income/expense)");
    return FALSE;
}

