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

GtkEntry *pentry1;
GtkEntry *pentry2;
GtkEntry *pentry3;
GtkEntry *pentry4;
GtkEntry *pentry5;
GtkEntry *pentry6;
GtkLabel *perror1;
GtkLabel *perror2;
GtkLabel *perror3;
GtkLabel *perror4;
GtkLabel *perror5;
GtkLabel *perror6;
GtkLabel *balance_label;

GtkWindow *main_window;
GtkWindow *show_popup;
GtkWindow *insert_popup;
GtkWindow *period_popup;
GtkDialog *balance_dialog;

GtkTextView *textview;
GtkTextBuffer *text_buffer;

struct Transaction transactions[1001];
int numTransactions = 0;
float currentAmount = 0;

struct Transaction aux;

//The functions for storing and working with data
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
    currentAmount = currentAmount + transaction.amount;
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
            {
                if(transactions[numTransactions].type[0] == 'e')
                    currentAmount = currentAmount - transactions[numTransactions].amount;
                else
                    currentAmount = currentAmount + transactions[numTransactions].amount;
                numTransactions = numTransactions + 1;
            }
        fclose(file);
    }
    else
        g_print("Failed to open the file :/");
}

//The functions for the entries
void entry_changed_period(GtkEntry *entry, GtkButton *period_submit_button)
{
    //we check all entries to be valid
    gboolean all_entries_valid = validate_all_entries_period();
    //We either enable or disable the submit button based on the valability
    gtk_widget_set_sensitive(GTK_WIDGET(period_submit_button), all_entries_valid);
}
gboolean validate_all_entries_period()
{
    gboolean e1 = check_pe1(pentry1, perror1);
    gboolean e2 = check_pe2(pentry2, perror2);
    gboolean e3 = check_pe3(pentry3, perror3);
    gboolean e4 = check_pe1(pentry4, perror4);
    gboolean e5 = check_pe2(pentry5, perror5);
    gboolean e6 = check_pe3(pentry6, perror6);
    if (e1 == FALSE || e2 == FALSE || e3 == FALSE || e4 == FALSE || e5 == FALSE || e6 == FALSE)
        return FALSE; 
    if (pentry1 > pentry4)
        {
            gtk_label_set_text(perror1, "The start of the period must be before the end of the period");
            return FALSE;
        }
    if (pentry1 == pentry4 && pentry2 > pentry5)
        {
            gtk_label_set_text(perror2, "The start of the period must be before the end of the period");
            return FALSE;
        }
    if (pentry1 == pentry4 && pentry2 == pentry5 && pentry3 > pentry6)
        {
            gtk_label_set_text(perror3, "The start of the period must be before the end of the period");
            return FALSE;
        }
    //We clear aux
    aux.year = 0;
    aux.month = 0;
    aux.day = 0;
    return TRUE;

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
    //We clear the entries
    clear_entry(GTK_WIDGET(entry1), entry1);
    clear_entry(GTK_WIDGET(entry2), entry2);
    clear_entry(GTK_WIDGET(entry3), entry3);
    clear_entry(GTK_WIDGET(entry4), entry4);
    clear_entry(GTK_WIDGET(entry5), entry5);
    clear_entry(GTK_WIDGET(entry6), entry6);

    gtk_widget_hide(GTK_WIDGET(insert_popup));
    gtk_widget_show_all(GTK_WIDGET(main_window));
}
void exit_button_show(GtkButton *button, gpointer user_data)
{
    clear_text_view(GTK_WIDGET(textview), text_buffer);
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
    //We clear the entries
    clear_entry(GTK_WIDGET(entry1), entry1);
    clear_entry(GTK_WIDGET(entry2), entry2);
    clear_entry(GTK_WIDGET(entry3), entry3);
    clear_entry(GTK_WIDGET(entry4), entry4);
    clear_entry(GTK_WIDGET(entry5), entry5);
    clear_entry(GTK_WIDGET(entry6), entry6);
    //We clear the labels
    gtk_label_set_text(error1, "");
    gtk_label_set_text(error2, "");
    gtk_label_set_text(error3, "");
    gtk_label_set_text(error4, "");
    gtk_label_set_text(error5, "");
    gtk_label_set_text(error6, "");
    gtk_label_set_text(feedback, "Transaction saved successfully!");
    g_print("Submit button clicked!");
}
void period_button_clicked(GtkButton *button, gpointer user_data)
{
    gtk_widget_hide(GTK_WIDGET(main_window));
    gtk_widget_show_all(GTK_WIDGET(period_popup));
    g_print("Period button clicked!");
}
void period_submit_button_clicked(GtkButton *button, gpointer user_data)
{
    //We store the 2 dates
    struct Transaction start;
    start.year = atoi(gtk_entry_get_text(pentry1));
    start.month = atoi(gtk_entry_get_text(pentry2));
    start.day = atoi(gtk_entry_get_text(pentry3));
    struct Transaction end;
    end.year = atoi(gtk_entry_get_text(pentry4));
    end.month = atoi(gtk_entry_get_text(pentry5));
    end.day = atoi(gtk_entry_get_text(pentry6));

    //We clear the entries
    clear_entry(GTK_WIDGET(pentry1), pentry1);
    clear_entry(GTK_WIDGET(pentry2), pentry2);
    clear_entry(GTK_WIDGET(pentry3), pentry3);
    clear_entry(GTK_WIDGET(pentry4), pentry4);
    clear_entry(GTK_WIDGET(pentry5), pentry5);
    clear_entry(GTK_WIDGET(pentry6), pentry6);

    //We clear the labels
    gtk_label_set_text(perror1, "");
    gtk_label_set_text(perror2, "");
    gtk_label_set_text(perror3, "");
    gtk_label_set_text(perror4, "");
    gtk_label_set_text(perror5, "");
    gtk_label_set_text(perror6, "");

    //We open the show_popup window
    gtk_widget_hide(GTK_WIDGET(period_popup));
    gtk_widget_show_all(GTK_WIDGET(show_popup));
    gtk_text_buffer_set_text(text_buffer, "", -1);  //Clearing the buffer

    //We print the transactions in the period
    for (int i=0;i<=numTransactions;i++)
    {
        if (transactions[i].year < start.year || transactions[i].year > end.year)
            continue;
        if (transactions[i].year == start.year && transactions[i].month < start.month)
            continue;
        if (transactions[i].year == start.year && transactions[i].month == start.month && transactions[i].day < start.day)
            continue;
        if (transactions[i].year == end.year && transactions[i].month > end.month)
            continue;
        if (transactions[i].year == end.year && transactions[i].month == end.month && transactions[i].day > end.day)
            continue;
        char TransactionData[512];
        sprintf(TransactionData, "Date: %d/%d/%d, Description: %s, Amount: %f, Type: %s\n", transactions[i].day, transactions[i].month, transactions[i].year,
                transactions[i].description, transactions[i].amount, transactions[i].type);
        
        //We get the text buffer
        GtkTextBuffer *local_text_buffer = gtk_text_view_get_buffer(textview);

        //Append the transaction data to the text buffer
        gtk_text_buffer_insert_at_cursor(local_text_buffer, TransactionData, -1);
    }

}
void period_exit_button_clicked(GtkButton *button, gpointer user_data)
{
    //We clear the entries
    clear_entry(GTK_WIDGET(pentry1), pentry1);
    clear_entry(GTK_WIDGET(pentry2), pentry2);
    clear_entry(GTK_WIDGET(pentry3), pentry3);
    clear_entry(GTK_WIDGET(pentry4), pentry4);
    clear_entry(GTK_WIDGET(pentry5), pentry5);
    clear_entry(GTK_WIDGET(pentry6), pentry6);

    gtk_widget_hide(GTK_WIDGET(period_popup));
    gtk_widget_show_all(GTK_WIDGET(main_window));
}
void balance_button_clicked(GtkButton *button, gpointer user_data)
{
    //We print the balance in the label
    char balance[256];
    sprintf(balance, "Your current balance is: %f", currentAmount);
    gtk_label_set_text(balance_label, balance);
    //We open the balance dialog
    gtk_dialog_run(balance_dialog);
    
    gtk_widget_hide(GTK_WIDGET(balance_dialog));
    g_print("Balance button clicked!");


}
//The functions for the entries
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
        if(strcmp(text,"expense") == 0)
            if(currentAmount - aux.amount <= 0)
            {
                gtk_label_set_text(error6, "You don't have enough money for this expense");
                return FALSE;
            }
            else
                {
                    gtk_label_set_markup(GTK_LABEL(error6), "<span font_desc='30'><b>✔</b></span>");
                    strcpy(aux.type,text);
                    return TRUE;
                }
        gtk_label_set_markup(GTK_LABEL(error6), "<span font_desc='30'><b>✔</b></span>");
        strcpy(aux.type,text);
        return TRUE;
    }
    gtk_label_set_text(error6, "Please enter a valid type (income/expense)");
    return FALSE;
}

//We check if the two dates are valid
gboolean check_pe1(GtkEntry *entry, GtkLabel *perror1)
{
    const gchar *text = gtk_entry_get_text(entry); //gtk_entry_get_text returns a pointer to a string
    int number = atoi(text); //converts to int
    if(number > 2023 || number < 1960)
    {
        gtk_label_set_text(perror1, "Please enter a valid year, between 1960 and the current one");
        return FALSE;
    }
    gtk_label_set_markup(GTK_LABEL(perror1), "<span font_desc='30'><b>✔</b></span>");
    return TRUE;
}
gboolean check_pe2(GtkEntry *entry, GtkLabel *perror2)
{
    const gchar *text = gtk_entry_get_text(entry); //gtk_entry_get_text returns a pointer to a string
    int number = atoi(text); //converts to int
    if(number > 12 || number < 1)
    {
        gtk_label_set_text(perror2, "Please enter a valid month, in a numerical value");
        return FALSE;
    }
    gtk_label_set_markup(GTK_LABEL(perror2), "<span font_desc='30'><b>✔</b></span>");
    return TRUE;
}
gboolean check_pe3(GtkEntry *entry, GtkLabel *perror3)
{
    const gchar *text = gtk_entry_get_text(entry); //gtk_entry_get_text returns a pointer to a string
    int number = atoi(text); //converts to int
    if(aux.year % 4 == 0 && aux.month == 2)
        if(number < 1 || number > 29)
        {
            gtk_label_set_text(perror3, "Please enter a valid day");
            return FALSE;
        }
    else
    {
        if(aux.month == 2)
            if(number < 1 || number > 28)
            {
                gtk_label_set_text(perror3, "Please enter a valid day");
                return FALSE;
            }
        if(aux.month == 1 || aux.month == 3 || aux.month == 5 || aux.month == 7 || aux.month == 8 || aux.month == 10 || aux.month == 12)
        {
            if(number < 1 || number > 31)
            {
                gtk_label_set_text(perror3, "Please enter a valid day");
                return FALSE;
            }
        }
        else
        {
            if(number < 1 || number > 30)
            {
                gtk_label_set_text(perror3, "Please enter a valid day");
                return FALSE;
            }
        }
    }
    gtk_label_set_markup(GTK_LABEL(perror3), "<span font_desc='30'><b>✔</b></span>");
    aux.day = number;
    return TRUE;
}
//The functions for clearing the entries
void clear_text_view(GtkWidget *widget, gpointer data) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data));
    gtk_text_buffer_set_text(buffer, "", -1);
}
void clear_entry(GtkWidget *widget, gpointer data) {
    gtk_entry_set_text(GTK_ENTRY(data), "");
}

