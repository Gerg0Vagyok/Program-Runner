#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void show_error_dialog(const gchar *message) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_CLOSE,
                                               "%s", message);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void button_clicked(GtkWidget *widget, gpointer data) {
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *text = gtk_entry_get_text(entry);

    gchar command[256];

    int result = system(text);

    if (result == -1) {
        gchar error_message[256];
        g_snprintf(error_message, sizeof(error_message), "Error: %s", strerror(errno));
        show_error_dialog(error_message);
    } else if (WIFEXITED(result) && WEXITSTATUS(result) != 0) {
        gchar error_message[256];
        g_snprintf(error_message, sizeof(error_message), "Error: Command exited with status %d", WEXITSTATUS(result));
        show_error_dialog(error_message);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Text Box and Button");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *entry = gtk_entry_new();
    GtkWidget *button = gtk_button_new_with_label("Run Command");

    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), entry);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), box);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
