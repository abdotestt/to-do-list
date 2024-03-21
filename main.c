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

Task *tasks[MAX_TASKS]; // Tableau de pointeurs de t�ches
int num_tasks = 0;

void add_task() {
    if (num_tasks >= MAX_TASKS) {
        printf("La limite de t�ches est atteinte.\n");
        return;
    }

    Task *new_task = malloc(sizeof(Task)); // Allocation de m�moire pour une nouvelle t�che
    new_task->id = malloc(sizeof(int)); // Allocation de m�moire pour l'identifiant
    new_task->name = malloc(20 * sizeof(char)); // Allocation de m�moire pour le nom
    new_task->description = malloc(100 * sizeof(char)); // Allocation de m�moire pour la description
    new_task->priority = malloc(sizeof(int)); // Allocation de m�moire pour la priorit�
    new_task->due_date = malloc(20 * sizeof(char)); // Allocation de m�moire pour la date d'�ch�ance
    new_task->completed = malloc(sizeof(bool)); // Allocation de m�moire pour le statut de compl�tion

    printf("Le nom de la t�che : ");
    fgets(new_task->name, 20, stdin);
    printf("Description de la t�che : ");
    fgets(new_task->description, 100, stdin);
    printf("Priorit� (1 : normale 2 : urgent 3  : tres urgent) : ");
    scanf("%d", new_task->priority);
    printf("Date d'�ch�ance (YYYY-MM-DD) : ");
    scanf("%s", new_task->due_date);
    printf("Completed (1 pour terminer, 0 pour non terminer) : ");
    scanf("%d", new_task->completed);
    *new_task->id = num_tasks + 1;

    tasks[num_tasks++] = new_task;
    printf("T�che ajout�e avec succ�s.\n");
}

void display_tasks() {
    printf("+-----+---------------------+----------------------------------------------------+------------+---------------+-------------+\n");
    printf("| %-3s | %-9s | %-50s | %-10s | %-13s | %-10s |\n", "ID", "Nom", "Description", "Priorit�", "Date echeance", "Statut");
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
    printf("Entrez l'ID de la t�che � modifier : ");
    scanf("%d", &task_id);
    getchar();

    if (task_id < 1 || task_id > num_tasks) {
        printf("ID de t�che invalide.\n");
        return;
    }

    Task *task_to_modify = tasks[task_id - 1];
    printf("Nouveau nom de la t�che : ");
    fgets(task_to_modify->name, 20, stdin);
    printf("Nouvelle description de la t�che : ");
    fgets(task_to_modify->description, 100, stdin);
    printf("Nouvelle priorit� (1-5) : ");
    scanf("%d", task_to_modify->priority);
    printf("Nouvelle date d'�ch�ance (YYYY-MM-DD) : ");
    scanf("%s", task_to_modify->due_date);
    printf("T�che modifi�e avec succ�s.\n");
}

void deleteTaskById() {
    int task_id;
    printf("Entrez l'ID de la t�che � supprimer : ");
    scanf("%d", &task_id);
    getchar();

    int found = 0;
    for (int i = 0; i < num_tasks; i++) {
        if (*tasks[i]->id == task_id) {
            free(tasks[i]->id); // Lib�ration de la m�moire allou�e pour l'identifiant
            free(tasks[i]->name); // Lib�ration de la m�moire allou�e pour le nom
            free(tasks[i]->description); // Lib�ration de la m�moire allou�e pour la description
            free(tasks[i]->priority); // Lib�ration de la m�moire allou�e pour la priorit�
            free(tasks[i]->due_date); // Lib�ration de la m�moire allou�e pour la date d'�ch�ance
            free(tasks[i]->completed); // Lib�ration de la m�moire allou�e pour le statut de compl�tion
            free(tasks[i]); // Lib�ration de la m�moire allou�e pour la t�che elle-m�me
            // D�caler les t�ches pour combler le vide apr�s la suppression de la t�che
            for (int j = i; j < num_tasks - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            num_tasks--;
            found = 1;
            printf("T�che avec l'ID %d supprim�e avec succ�s.\n", task_id);
            break;
        }
    }
    if (!found) {
        printf("T�che avec l'ID %d non trouv�e.\n", task_id);
    }
}

void filterTasksByPriority() {
    int priority;
    printf("Entrez la priorit� (1 : normal 2 : urgent 3 : tres urgent) : ");
    scanf("%d", &priority);

    printf("T�ches avec priorit� %d :\n", priority);
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

    // Lib�ration de la m�moire allou�e pour chaque t�che
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
