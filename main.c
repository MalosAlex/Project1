#include <gtk/gtk.h>
#include <stdio.h>
#include "library.h"

int main(int argc, char *argv[])
{
    //Initializing GTK
    gtk_init(&argc,&argv);
    load_transaction("data_storage.txt");

    //Creating a GtkBuilder to load the Glade file in which the application was designed
    GtkBuilder *builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder,"project_gui.glade", NULL) == 0)
    {
        g_error("Failed to load Glade file");
        return 1;
    }

    //Retrieving widgets

    //Retrieving the windows
    main_window = GTK_WINDOW(gtk_builder_get_object(builder,"main_window"));
    show_popup = GTK_WINDOW(gtk_builder_get_object(builder, "show_popup"));
    insert_popup = GTK_WINDOW(gtk_builder_get_object(builder, "insert_popup"));
    period_popup = GTK_WINDOW(gtk_builder_get_object(builder, "period_popup"));

    //main window
    GtkBox *box_main = GTK_BOX(gtk_builder_get_object(builder, "box_main"));
    GtkButton *insert_button = GTK_BUTTON(gtk_builder_get_object(builder, "insert_button"));
    GtkButton *show_button = GTK_BUTTON(gtk_builder_get_object(builder, "show_button"));
    GtkButton *exit_button = GTK_BUTTON(gtk_builder_get_object(builder, "exit_button"));
    GtkButton *period_button = GTK_BUTTON(gtk_builder_get_object(builder, "period_button"));
    GtkButton *balance_button = GTK_BUTTON(gtk_builder_get_object(builder, "balance_button"));
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
    entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry1"));
    entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry2"));
    entry3 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3"));
    entry4 = GTK_ENTRY(gtk_builder_get_object(builder, "entry4"));
    entry5 = GTK_ENTRY(gtk_builder_get_object(builder, "entry5"));
    entry6 = GTK_ENTRY(gtk_builder_get_object(builder, "entry6"));
    GtkButton *insert_exit_button = GTK_BUTTON(gtk_builder_get_object(builder, "insert_exit_button"));
    GtkButton *submit_button = GTK_BUTTON(gtk_builder_get_object(builder, "submit_button"));
    error1 = GTK_LABEL(gtk_builder_get_object(builder, "error1"));
    error2 = GTK_LABEL(gtk_builder_get_object(builder, "error2"));
    error3 = GTK_LABEL(gtk_builder_get_object(builder, "error3"));
    error4 = GTK_LABEL(gtk_builder_get_object(builder, "error4"));
    error5 = GTK_LABEL(gtk_builder_get_object(builder, "error5"));
    error6 = GTK_LABEL(gtk_builder_get_object(builder, "error6"));
    feedback = GTK_LABEL(gtk_builder_get_object(builder, "feedback"));

    //show window
    GtkBox *box_show = GTK_BOX(gtk_builder_get_object(builder, "box_show"));
    textview = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "textview"));
    GtkButton *show_exit_button = GTK_BUTTON(gtk_builder_get_object(builder, "show_exit_button"));
    text_buffer = gtk_text_buffer_new(NULL);
    gtk_text_view_set_buffer(textview, text_buffer);

    //period window
    GtkGrid *grid_period = GTK_GRID(gtk_builder_get_object(builder, "grid_period"));
    pentry1 = GTK_ENTRY(gtk_builder_get_object(builder, "pentry1"));
    pentry2 = GTK_ENTRY(gtk_builder_get_object(builder, "pentry2"));
    pentry3 = GTK_ENTRY(gtk_builder_get_object(builder, "pentry3"));
    pentry4 = GTK_ENTRY(gtk_builder_get_object(builder, "pentry4"));
    pentry5 = GTK_ENTRY(gtk_builder_get_object(builder, "pentry5"));
    pentry6 = GTK_ENTRY(gtk_builder_get_object(builder, "pentry6"));
    GtkButton *period_submit_button = GTK_BUTTON(gtk_builder_get_object(builder, "period_submit_button"));
    GtkButton *period_exit_button = GTK_BUTTON(gtk_builder_get_object(builder, "period_exit_button"));
    perror1 = GTK_LABEL(gtk_builder_get_object(builder, "perror1"));
    perror2 = GTK_LABEL(gtk_builder_get_object(builder, "perror2"));
    perror3 = GTK_LABEL(gtk_builder_get_object(builder, "perror3"));
    perror4 = GTK_LABEL(gtk_builder_get_object(builder, "perror4"));
    perror5 = GTK_LABEL(gtk_builder_get_object(builder, "perror5"));
    perror6 = GTK_LABEL(gtk_builder_get_object(builder, "perror6"));
    GtkLabel *plabel1 = GTK_LABEL(gtk_builder_get_object(builder, "plabel1"));
    GtkLabel *plabel2 = GTK_LABEL(gtk_builder_get_object(builder, "plabel2"));
    GtkLabel *plabel3 = GTK_LABEL(gtk_builder_get_object(builder, "plabel3"));
    GtkLabel *plabel4 = GTK_LABEL(gtk_builder_get_object(builder, "plabel4"));
    GtkLabel *plabel5 = GTK_LABEL(gtk_builder_get_object(builder, "plabel5"));
    GtkLabel *plabel6 = GTK_LABEL(gtk_builder_get_object(builder, "plabel6"));
    GtkLabel *pFeedback = GTK_LABEL(gtk_builder_get_object(builder, "pFeedback"));
    GtkLabel *plabel01 = GTK_LABEL(gtk_builder_get_object(builder, "plabel01"));
    GtkLabel *plabel02 = GTK_LABEL(gtk_builder_get_object(builder, "plabel02"));

    //balance dialog
    balance_dialog = GTK_DIALOG(gtk_builder_get_object(builder, "balance_dialog"));
    balance_label = GTK_LABEL(gtk_builder_get_object(builder, "balance_label"));
    

    //setting up the buttons
    g_signal_connect(G_OBJECT(insert_button), "clicked", G_CALLBACK(insert_button_clicked), NULL);
    g_signal_connect(G_OBJECT(show_button), "clicked", G_CALLBACK(show_button_clicked), NULL);
    g_signal_connect(G_OBJECT(exit_button), "clicked", G_CALLBACK(exit_button_clicked), NULL);
    g_signal_connect(G_OBJECT(show_exit_button), "clicked", G_CALLBACK(exit_button_show), NULL);
    g_signal_connect(G_OBJECT(insert_exit_button), "clicked", G_CALLBACK(exit_button_insert), NULL);
    g_signal_connect(G_OBJECT(submit_button), "clicked", G_CALLBACK(submit_button_clicked), NULL);
    g_signal_connect(G_OBJECT(period_submit_button), "clicked", G_CALLBACK(period_submit_button_clicked), NULL);
    g_signal_connect(G_OBJECT(period_exit_button), "clicked", G_CALLBACK(period_exit_button_clicked), NULL);
    g_signal_connect(G_OBJECT(period_button), "clicked", G_CALLBACK(period_button_clicked), NULL);
    g_signal_connect(G_OBJECT(balance_button), "clicked", G_CALLBACK(balance_button_clicked), NULL);

    //setting up the text entries
    //If any text is changed I go into the function entry_changed to check if all entries are good
    g_signal_connect(G_OBJECT(entry1), "changed", G_CALLBACK(entry_changed),submit_button);
    g_signal_connect(G_OBJECT(entry2), "changed", G_CALLBACK(entry_changed),submit_button);
    g_signal_connect(G_OBJECT(entry3), "changed", G_CALLBACK(entry_changed),submit_button);
    g_signal_connect(G_OBJECT(entry4), "changed", G_CALLBACK(entry_changed),submit_button);
    g_signal_connect(G_OBJECT(entry5), "changed", G_CALLBACK(entry_changed),submit_button);
    g_signal_connect(G_OBJECT(entry6), "changed", G_CALLBACK(entry_changed),submit_button);
    g_signal_connect(G_OBJECT(pentry1), "changed", G_CALLBACK(entry_changed_period),period_submit_button);
    g_signal_connect(G_OBJECT(pentry2), "changed", G_CALLBACK(entry_changed_period),period_submit_button);
    g_signal_connect(G_OBJECT(pentry3), "changed", G_CALLBACK(entry_changed_period),period_submit_button);
    g_signal_connect(G_OBJECT(pentry4), "changed", G_CALLBACK(entry_changed_period),period_submit_button);
    g_signal_connect(G_OBJECT(pentry5), "changed", G_CALLBACK(entry_changed_period),period_submit_button);
    g_signal_connect(G_OBJECT(pentry6), "changed", G_CALLBACK(entry_changed_period),period_submit_button);



    //Setting the texts for the labels
    gtk_label_set_text(contact,"Program made by Malos Alexandru-Razvan. Contact: malosalexandru2004@gmail.com");
    gtk_label_set_text(label1,"Year of transaction:");
    gtk_label_set_text(label2,"Month of transaction:");
    gtk_label_set_text(label3,"Day of transaction:");
    gtk_label_set_text(label4,"Description of the transaction");
    gtk_label_set_text(label5,"Amount:");
    gtk_label_set_text(label6,"Type(income/expense)");
    gtk_label_set_text(label01,"Please introduce");
    gtk_label_set_text(label02,"the data below");
    gtk_label_set_text(error1, "");
    gtk_label_set_text(error2, "");
    gtk_label_set_text(error3, "");
    gtk_label_set_text(error4, "");
    gtk_label_set_text(error5, "");
    gtk_label_set_text(error6, "");
    gtk_label_set_text(feedback, "Feedback on input");
    gtk_label_set_text(perror1, "");
    gtk_label_set_text(perror2, "");
    gtk_label_set_text(perror3, "");
    gtk_label_set_text(perror4, "");
    gtk_label_set_text(perror5, "");
    gtk_label_set_text(perror6, "");
    gtk_label_set_text(plabel1, "Start of the period year");
    gtk_label_set_text(plabel2, "Start of the period month");
    gtk_label_set_text(plabel3, "Start of the period day");
    gtk_label_set_text(plabel4, "End of the period year");
    gtk_label_set_text(plabel5, "End of the period month");
    gtk_label_set_text(plabel6, "End of the period day");
    gtk_label_set_text(pFeedback, "Feedback on input");
    gtk_label_set_text(plabel01, "Please introduce");
    gtk_label_set_text(plabel02, "the two dates");

    //Shwoing the main window
    gtk_widget_show_all(GTK_WIDGET(main_window));

    //Running the GTK main loop
    gtk_main();
}
