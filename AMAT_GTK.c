#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the encryption key
static const char *key = "1234567890abcdef";

// Encrypt a string
static char *my_encrypt(const char *plaintext) {
    // Create a buffer to store the encrypted text
    char *ciphertext = malloc(strlen(plaintext) * 2 + 1); // Each character can be represented by 2 hexadecimal digits

    // Iterate over the plaintext characters and encrypt them
    for (int i = 0; i < strlen(plaintext); i++) {
        sprintf(ciphertext + i * 2, "%02x", plaintext[i] ^ key[i % strlen(key)]);
    }

    // Null-terminate the encrypted text
    ciphertext[strlen(plaintext) * 2] = '\0';

    // Return the encrypted text
    return ciphertext;
}

// Decrypt a string
static char *decrypt(const char *ciphertext) {
    // Create a buffer to store the decrypted text
    char *plaintext = malloc(strlen(ciphertext) / 2 + 1); // Each pair of hexadecimal digits corresponds to one character

    // Iterate over the ciphertext characters and decrypt them
    for (int i = 0; i < strlen(ciphertext) / 2; i++) {
        sscanf(ciphertext + i * 2, "%02x", (unsigned int *)&plaintext[i]);
        plaintext[i] ^= key[i % strlen(key)];
    }

    // Null-terminate the decrypted text
    plaintext[strlen(ciphertext) / 2] = '\0';

    // Return the decrypted text
    return plaintext;
}

// The encrypt button click handler
static void encrypt_button_clicked(GtkWidget *widget, gpointer data) {
    // Get the text from the input entry
    const gchar *plaintext = gtk_entry_get_text(GTK_ENTRY(data));

    // Encrypt the text
    char *ciphertext = my_encrypt(plaintext);

    // Update the output entry text with the encrypted text
    gtk_entry_set_text(GTK_ENTRY(g_object_get_data(G_OBJECT(widget), "output")), ciphertext);

    // Free the allocated memory
    free(ciphertext);

    // Disable the encrypt button and enable the decrypt button
    gtk_widget_set_sensitive(widget, FALSE);
    gtk_widget_set_sensitive(g_object_get_data(G_OBJECT(widget), "decrypt_button"), TRUE);
}

// The decrypt button click handler
static void decrypt_button_clicked(GtkWidget *widget, gpointer data) {
    // Get the text from the input entry
    const gchar *ciphertext = gtk_entry_get_text(GTK_ENTRY(data));

    // Decrypt the text
    char *plaintext = decrypt(ciphertext);

    // Update the output entry text with the decrypted text
    gtk_entry_set_text(GTK_ENTRY(g_object_get_data(G_OBJECT(widget), "output")), plaintext);

    // Free the allocated memory
    free(plaintext);

    // Disable the decrypt button and enable the encrypt button
    gtk_widget_set_sensitive(widget, FALSE);
    gtk_widget_set_sensitive(g_object_get_data(G_OBJECT(widget), "encrypt_button"), TRUE);
}

// The main function
int main(int argc, char *argv[]) {
    // Initialize the GTK+ library
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Encryption/Decryption Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); // Set the default size of the window
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Center the window
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create input and output entry widgets
    GtkWidget *input_entry = gtk_entry_new();
    GtkWidget *output_entry = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(output_entry), FALSE); // make output entry read-only

    // Create encrypt and decrypt buttons
    GtkWidget *encrypt_button = gtk_button_new_with_label("Encrypt");
    GtkWidget *decrypt_button = gtk_button_new_with_label("Decrypt");

    // Create a box to hold widgets
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(box), input_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), output_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), encrypt_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), decrypt_button, FALSE, FALSE, 0);

    // Connect buttons to their respective click handlers
    g_object_set_data(G_OBJECT(encrypt_button), "output", output_entry);
    g_object_set_data(G_OBJECT(encrypt_button), "decrypt_button", decrypt_button);
    g_signal_connect(encrypt_button, "clicked", G_CALLBACK(encrypt_button_clicked), input_entry);

    g_object_set_data(G_OBJECT(decrypt_button), "output", output_entry);
    g_object_set_data(G_OBJECT(decrypt_button), "encrypt_button", encrypt_button);
    g_signal_connect(decrypt_button, "clicked", G_CALLBACK(decrypt_button_clicked), input_entry);

    // Add box to window and show all widgets
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);

    // Start the GTK+ main loop
    gtk_main();

    return 0;
}
