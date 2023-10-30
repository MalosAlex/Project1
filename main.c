#include <gtk/gtk.h>
#include <stdio.h>

// Define global window pointers
GtkWindow *main_window;
GtkWindow *show_popup;
GtkWindow *insert_popup;

//Defining other global widgets
GtkTextView *textview;
GtkTextBuffer *text_buffer;

//The data structures
struct Transaction{
    int year, month, day;
    char description[256];
    float amount;
    char type[8]; //income or expense
}transactions[1001];

int numTransactions = 0;

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

int main(int argc, char *argv[])
{
    //Initializing GTK
    gtk_init(&argc,&argv);

    //Creating a GtkBuilder to load the Glade file in which the application was designed
    GtkBuilder *builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder,"project_gui.glade", NULL) == 0)
    {
        g_error("Failed to load Glade file");
        return 1;
    }
    transactions[0].year = 2004;
    transactions[0].month = 8;
    transactions[0].day = 18;
    strcpy(transactions[0].description,"test");
    transactions[0].amount = 320.45;
    strcpy(transactions[0].type,"income");
    numTransactions = 1;
    //Retrieving widgets
    //Retrieving the windows
    main_window = GTK_WINDOW(gtk_builder_get_object(builder,"main_window"));
    show_popup = GTK_WINDOW(gtk_builder_get_object(builder, "show_popup"));
    insert_popup = GTK_WINDOW(gtk_builder_get_object(builder, "insert_popup"));
    //main window
    GtkBox *box_main = GTK_BOX(gtk_builder_get_object(builder, "box_main"));
    GtkButton *insert_button = GTK_BUTTON(gtk_builder_get_object(builder, "insert_button"));
    GtkButton *show_button = GTK_BUTTON(gtk_builder_get_object(builder, "show_button"));
    GtkButton *exit_button = GTK_BUTTON(gtk_builder_get_object(builder, "exit_button"));
    GtkLabel *contact = GTK_LABEL(gtk_builder_get_object(builder, "contact"));
    //insert window
    GtkGrid *grid_insert = GTK_GRID(gtk_builder_get_object(builder, "grid_insert"));
    GtkLabel *label1 = GTK_LABEL(gtk_builder_get_object(builder, "label1"));
    GtkLabel *label2 = GTK_LABEL(gtk_builder_get_object(builder, "label2"));
    GtkLabel *label3 = GTK_LABEL(gtk_builder_get_object(builder, "label3"));
    GtkLabel *label4 = GTK_LABEL(gtk_builder_get_object(builder, "label4"));
    GtkLabel *label5 = GTK_LABEL(gtk_builder_get_object(builder, "label5"));
    GtkLabel *label6 = GTK_LABEL(gtk_builder_get_object(builder, "label6"));
    GtkLabel *label01 = GTK_LABEL(gtk_builder_get_object(builder, "label01"));
    GtkLabel *label02 = GTK_LABEL(gtk_builder_get_object(builder, "label02"));
    GtkEntry *entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry1"));
    GtkEntry *entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry2"));
    GtkEntry *entry3 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3"));
    GtkEntry *entry4 = GTK_ENTRY(gtk_builder_get_object(builder, "entry4"));
    GtkEntry *entry5 = GTK_ENTRY(gtk_builder_get_object(builder, "entry5"));
    GtkEntry *entry6 = GTK_ENTRY(gtk_builder_get_object(builder, "entry6"));
    GtkButton *insert_exit_button = GTK_BUTTON(gtk_builder_get_object(builder, "insert_exit_button"));
    GtkButton *submit_button = GTK_BUTTON(gtk_builder_get_object(builder, "submit_button"));
    //show window
    GtkBox *box_show = GTK_BOX(gtk_builder_get_object(builder, "box_show"));
    textview = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "textview"));
    GtkButton *show_exit_button = GTK_BUTTON(gtk_builder_get_object(builder, "show_exit_button"));
    text_buffer = gtk_text_buffer_new(NULL);
    gtk_text_view_set_buffer(textview, text_buffer);

    //setting up the buttons
    g_signal_connect(G_OBJECT(insert_button), "clicked", G_CALLBACK(insert_button_clicked), NULL);
    g_signal_connect(G_OBJECT(show_button), "clicked", G_CALLBACK(show_button_clicked), NULL);
    g_signal_connect(G_OBJECT(exit_button), "clicked", G_CALLBACK(exit_button_clicked), NULL);
    g_signal_connect(G_OBJECT(show_exit_button), "clicked", G_CALLBACK(exit_button_show), NULL);
    g_signal_connect(G_OBJECT(insert_exit_button), "clicked", G_CALLBACK(exit_button_insert), NULL);
    g_signal_connect(G_OBJECT(submit_button), "clicked", G_CALLBACK(submit_button_clicked), NULL);

    //Setting the texts for the labels
    gtk_label_set_text(contact,"Program made by Malos Alexandru. Contact: malosalexandru@gmail.com");
    gtk_label_set_text(label1,"Year of transaction:");
    gtk_label_set_text(label2,"Month of transaction:");
    gtk_label_set_text(label3,"Day of transaction:");
    gtk_label_set_text(label4,"Description of the transaction");
    gtk_label_set_text(label5,"Amount:");
    gtk_label_set_text(label6,"Type(income/expense)");
    gtk_label_set_text(label01,"Please introduce");
    gtk_label_set_text(label02,"the data below");

    //Shwoing the main window
    gtk_widget_show_all(GTK_WIDGET(main_window));

    //Running the GTK main loop
    gtk_main();
}