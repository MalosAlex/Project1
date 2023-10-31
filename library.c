#include <stdio.h>
#include <gtk/gtk.h>
#include "library.h"
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
    numTransactions++;
    fclose(file);
}
void load_transaction(const char* filename)
{
    FILE* file = fopen(filename, "r"); //read
    if(file)
    {
        numTransactions = 0;
        while(numTransactions < 1001 && fscanf(file, "%d %d %d %s %f %7s\n", &transactions[numTransactions].year, &transactions[numTransactions].month,
                &transactions[numTransactions].day, transactions[numTransactions].description, &transactions[numTransactions].amount,
                transactions[numTransactions].type) == 6) //checks if it reads a value for every variable
            numTransactions++;
        fclose(file);
    }
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
    g_print("Submit button clicked!");
}