#include <gtk/gtk.h>
#include <stdio.h>

#include "lexicalAnalysis.h"

// Global variables
GtkWidget *window;
GtkWidget *TINYView;
GtkWidget *resView;
char *filename;         // Save the file user read

void readFileAndPrintTotheView(char *filename) {
    FILE *fp = NULL;
    char buff[255];
    GtkTextBuffer *textBuffer = gtk_text_view_get_buffer((GtkTextView*)TINYView);
    GtkTextIter iter;

    gtk_text_buffer_get_iter_at_offset(textBuffer, &iter, 0);

    if ((fp = fopen(filename, "rb")) == NULL) {
        printf("\nCannot open file!");
    }
    else {
        while (fgets(buff, 255, fp) != NULL) {
            gtk_text_buffer_insert(textBuffer, &iter, buff, -1);
        }
    }

    fclose(fp);
}

void printToresView() {
    FILE *fpRead = NULL;
    char buff[BUFFER_SIZE];
    GtkTextBuffer *textBuffer = gtk_text_view_get_buffer((GtkTextView*)resView);
    GtkTextIter iter;
    char tokenFilepath[BUFFER_SIZE] = ".\\bin\\token.txt";

    gtk_text_buffer_get_iter_at_offset(textBuffer, &iter, 0);

    if ((fpRead = fopen(tokenFilepath, "rb+")) == NULL) {
        // printf("\nCannot open file: %s!", tokenFilepath);

        if ((fpRead = fopen(".\\token.txt", "rb+")) == NULL) {
            printf("\nCannot open file: %s!", tokenFilepath);
            
            return;
        }
    }
    while (fgets(buff, 255, fpRead) != NULL) {
        gtk_text_buffer_insert(textBuffer, &iter, buff, -1);
    }

    fclose(fpRead);
}

static gboolean readFile()
{
    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new("Open File",
                                         (GtkWindow*)window,
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                         GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                         NULL);

    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));

        readFileAndPrintTotheView(filename);
    }

    gtk_widget_destroy(dialog);
}

static gboolean lexicalAnalysis()
{
    getToken(filename);

    printToresView();
}

int main(int argc, char *argv[]) {
    // Initial the GTK
    gtk_init(&argc, &argv);

    // Create a new window and set some attributes
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);   // When pressed the close button, the program exit
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);        // Set the location of the window in the center of the screen
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 800);              // Set the size of program
    gtk_window_set_title(GTK_WINDOW(window), "TINY+ Analyzer");             // Set the title of the window

    // Create a vertical container to hold the horizontal containers
    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);

    // Create a horizontal container to hold buttons
    // 'TRUE' means the size of widget is equal
    // '10' means the px of the gap
    GtkWidget *buttonBox = gtk_hbox_new(TRUE, 10);

    // Create buttons to read file, lexical analysis
    GtkWidget *readButton   = gtk_button_new_with_label("Read TINY File");
    GtkWidget *lexAnaButton = gtk_button_new_with_label("Lexical Analysis");

    // Add the buttons to buttonBox
    gtk_box_pack_start(GTK_BOX(buttonBox), readButton, TRUE, TRUE, 15);
    gtk_box_pack_start(GTK_BOX(buttonBox), lexAnaButton, TRUE, TRUE, 15);

    // Add the event
    g_signal_connect_swapped(readButton, "button-press-event", G_CALLBACK (readFile), NULL);
    g_signal_connect_swapped(lexAnaButton, "button-press-event", G_CALLBACK (lexicalAnalysis), NULL);

    // Create a horizontal container to hold textfield
    GtkWidget *textBox   = gtk_hbox_new(TRUE, 10);

    // Create views to show text and set the attribute
    TINYView  = gtk_text_view_new();
    resView   = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(TINYView), GTK_WRAP_WORD);    // make the text reach the edge to get to the next line
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(resView), GTK_WRAP_WORD);

    // Make text view scrolled
    GtkWidget *scrolledWindow4TINYView = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *scrolledWindow4ResView = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolledWindow4TINYView), TINYView);
    gtk_container_add(GTK_CONTAINER(scrolledWindow4ResView), resView);

    // Add the textviews to textBox
    gtk_box_pack_start(GTK_BOX(textBox), scrolledWindow4TINYView, TRUE, TRUE, 15);
    gtk_box_pack_start(GTK_BOX(textBox), scrolledWindow4ResView, TRUE, TRUE, 15);

    // Add the horizontal boxs to the vbox
    gtk_box_pack_start(GTK_BOX(vbox), buttonBox, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), textBox, TRUE, TRUE, 20);

    // Add the vbox to the windows
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Set the all the widgets visible
    gtk_widget_show_all(window);    // Set the window visible

    // Main function
    gtk_main();
    return 0;
}