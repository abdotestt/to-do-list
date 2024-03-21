#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TASKS 100

typedef struct {
    int *id;
    char *name;
    char *description;
    int *priority;
    char *due_date;
    bool *completed;
} Task;

Task *tasks[MAX_TASKS]; // Tableau de pointeurs de tâches
int num_tasks = 0;

void add_task() {
    if (num_tasks >= MAX_TASKS) {
        printf("La limite de tâches est atteinte.\n");
        return;
    }

    Task *new_task = malloc(sizeof(Task)); // Allocation de mémoire pour une nouvelle tâche
    new_task->id = malloc(sizeof(int)); // Allocation de mémoire pour l'identifiant
    new_task->name = malloc(20 * sizeof(char)); // Allocation de mémoire pour le nom
    new_task->description = malloc(100 * sizeof(char)); // Allocation de mémoire pour la description
    new_task->priority = malloc(sizeof(int)); // Allocation de mémoire pour la priorité
    new_task->due_date = malloc(20 * sizeof(char)); // Allocation de mémoire pour la date d'échéance
    new_task->completed = malloc(sizeof(bool)); // Allocation de mémoire pour le statut de complétion

    printf("Le nom de la tâche : ");
    fgets(new_task->name, 20, stdin);
    printf("Description de la tâche : ");
    fgets(new_task->description, 100, stdin);
    printf("Priorité (1 : normale 2 : urgent 3  : tres urgent) : ");
    scanf("%d", new_task->priority);
    printf("Date d'échéance (YYYY-MM-DD) : ");
    scanf("%s", new_task->due_date);
    printf("Completed (1 pour terminer, 0 pour non terminer) : ");
    scanf("%d", new_task->completed);
    *new_task->id = num_tasks + 1;

    tasks[num_tasks++] = new_task;
    printf("Tâche ajoutée avec succès.\n");
}

void display_tasks() {
    printf("+-----+---------------------+----------------------------------------------------+------------+---------------+-------------+\n");
    printf("| %-3s | %-9s | %-50s | %-10s | %-13s | %-10s |\n", "ID", "Nom", "Description", "Priorité", "Date echeance", "Statut");
    printf("+-----+---------------------+----------------------------------------------------+------------+---------------+-------------+\n");

    for (int i = 0; i < num_tasks; i++) {
        printf("| %-3d | %-9s | %-50s | %-10d | %-13s | %-10s |\n",
               *tasks[i]->id,
               *tasks[i]->name,
               *tasks[i]->description,
               *tasks[i]->priority,
               *tasks[i]->due_date,
               *tasks[i]->completed);
    }

    printf("+-----+---------------------+----------------------------------------------------+------------+---------------+-------------+\n");
}

void modify_task() {
    int task_id;
    printf("Entrez l'ID de la tâche à modifier : ");
    scanf("%d", &task_id);
    getchar();

    if (task_id < 1 || task_id > num_tasks) {
        printf("ID de tâche invalide.\n");
        return;
    }

    Task *task_to_modify = tasks[task_id - 1];
    printf("Nouveau nom de la tâche : ");
    fgets(task_to_modify->name, 20, stdin);
    printf("Nouvelle description de la tâche : ");
    fgets(task_to_modify->description, 100, stdin);
    printf("Nouvelle priorité (1-5) : ");
    scanf("%d", task_to_modify->priority);
    printf("Nouvelle date d'échéance (YYYY-MM-DD) : ");
    scanf("%s", task_to_modify->due_date);
    printf("Tâche modifiée avec succès.\n");
}

void deleteTaskById() {
    int task_id;
    printf("Entrez l'ID de la tâche à supprimer : ");
    scanf("%d", &task_id);
    getchar();

    int found = 0;
    for (int i = 0; i < num_tasks; i++) {
        if (*tasks[i]->id == task_id) {
            free(tasks[i]->id); // Libération de la mémoire allouée pour l'identifiant
            free(tasks[i]->name); // Libération de la mémoire allouée pour le nom
            free(tasks[i]->description); // Libération de la mémoire allouée pour la description
            free(tasks[i]->priority); // Libération de la mémoire allouée pour la priorité
            free(tasks[i]->due_date); // Libération de la mémoire allouée pour la date d'échéance
            free(tasks[i]->completed); // Libération de la mémoire allouée pour le statut de complétion
            free(tasks[i]); // Libération de la mémoire allouée pour la tâche elle-même
            // Décaler les tâches pour combler le vide après la suppression de la tâche
            for (int j = i; j < num_tasks - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            num_tasks--;
            found = 1;
            printf("Tâche avec l'ID %d supprimée avec succès.\n", task_id);
            break;
        }
    }
    if (!found) {
        printf("Tâche avec l'ID %d non trouvée.\n", task_id);
    }
}

void filterTasksByPriority() {
    int priority;
    printf("Entrez la priorité (1 : normal 2 : urgent 3 : tres urgent) : ");
    scanf("%d", &priority);

    printf("Tâches avec priorité %d :\n", priority);
    for (int i = 0; i < num_tasks; i++) {
        if (*tasks[i]->priority == priority) {
            printf("%s\n", *tasks[i]->description);
        }
    }
}

int main() {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Ajouter une tache\n");
        printf("2. Afficher les taches\n");
        printf("3. Modifier une tache\n");
        printf("4. Supprimer une tache\n");
        printf("5. Filtrer les taches par priorite\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                add_task();
                break;
            case 2:
                display_tasks();
                break;
            case 3:

                modify_task();
                break;
            case 4:
                deleteTaskById();
                break;
            case 5:
                filterTasksByPriority();
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 0);

    // Libération de la mémoire allouée pour chaque tâche
    for (int i = 0; i < num_tasks; i++) {
        free(tasks[i]->id);
        free(tasks[i]->name);
        free(tasks[i]->description);
        free(tasks[i]->priority);
        free(tasks[i]->due_date);
        free(tasks[i]->completed);
        free(tasks[i]);
    }

    return 0;
}
