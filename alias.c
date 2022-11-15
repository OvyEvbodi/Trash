#include "alias.h"
#include "main.h"


/**
 * split_alias - calculates the length of an alias definition
 * and its expansion
 * @alias_str: the string defining an alias
 * @alias: the alias
 * @expanded: th command to expand alias into
 *
 * Return: void
*/

void split_alias(char *alias_str, char **alias, char **expanded, int *shrt_len, int *full_len)
{
	int i = 0;
	char full[BUFF_SIZE], shrt[BUFF_SIZE / 4];

	*shrt_len = 0;
	*full_len = 0;
	while (alias_str[i])
	{
		if (alias_str[i] == '=')
		{
			i++;
			if (alias_str[i] == '\'' || alias_str[i] == '"')
			{
				i++;
				for (*full_len = 0; alias_str[i]; i++)
					full[(*full_len)++] = alias_str[i];
					full[(*full_len) - 1] = '\0';
				(*full_len)--;
				break;
			}
			else
			{
				for (*full_len = 0; alias_str[i] != ' ' && alias_str[i]; i++)
					full[(*full_len)++] = alias_str[i];
				full[*full_len] = '\0';
				break;
			}
		}
		shrt[(*shrt_len)++] = alias_str[i++];
	}

	*alias = _strdup(shrt);
	*expanded = _strdup(full);

}

/**
 * add_alias - adds an alias definition to the alias list,
 * or overwrites an existing definition
 * @head: a pointer to the head pointer
 * @alias: the alias
 * @expanded: th command to expand alias into
 *
 * Return: a pointer to the new alias,
 * otherwise, NULL
*/


alias_t *add_alias(alias_t **head, char **alias, char **expanded,
int *shrt_len, int *full_len)
{
	alias_t *new;
	alias_t *temp = *head;

	new = malloc(sizeof(alias_t));
	if (!new)
		return (NULL);
	new->cmd = "alias";
	new->shrt = _strdup(*alias);
	new->full = _strdup(*expanded);
	new->s_len = *shrt_len;
	new->f_len = *full_len;
	new->equal = '=';
	new->pre = '\'';
	new->post = '\'';
	new->link = NULL;

	if (!*head)
	{
		*head = new;
		return (new);
	}

	while (temp->link)
		temp = temp->link;
	temp->link = new;

	// free(alias);
	// free(expanded);

	return (new);
}

/**
 * print_alias - prints a list of aliases
 * @head: a pointer to the first node
 *
 * Return: ok, if successful,
 * otherwise, NULL
*/

char *print_alias(alias_t *head)
{
	int index = 0;
	char buffer[BUFF_SIZE];
	/*is this better done dynamically?*/
	
	if (!head)
		return (NULL);
	while (head)
	{

		for (index = 0; index < 5;)
		{
			buffer[index++] = *(head->cmd);
			(head->cmd)++;
		}
		buffer[index++] = ' ';
		while (head->s_len--)
		{
			buffer[index++] = *(head->shrt);
			(head->shrt)++;
		}
		buffer[index++] = head->equal;
		buffer[index++] = head->pre;
		while (head->f_len--)
		{
			buffer[index++] = *(head->full);
			(head->full)++;
		}
		buffer[index++] = head->post;
		buffer[index++] = '\n';
		buffer[index++] = '\0';
		write (1, buffer, index);
		
		/*figure out what to free, and what may be lost*/

		head = head->link;
	}
	return ("ok");
}

/**
 * _alias - handles alias builtin
 * 
 *
*/

char *_alias(char **arr_tokens, char *buffer)
{
	char *alias = NULL, *expanded = NULL;
	int shrt_len = 0, full_len = 0, i = 0;
	alias_t *head = NULL, *node;

	split_alias("push='smore and'", &alias, &expanded, &shrt_len, &full_len);
	node = add_alias(&head, &alias, &expanded, &shrt_len, &full_len);
	split_alias("p='git push origin main'", &alias, &expanded, &shrt_len, &full_len);
	node = add_alias(&head, &alias, &expanded, &shrt_len, &full_len);

	if (!arr_tokens[1])
		print_alias(head);
	else
	{
		while (arr_token[i++])
		{
			/*call function to replace arr_token with head->full, to be continued...*/
		}
	}
	return ("ok");
}

/**
 * free_alias_list - Deletes the aliases linked list.
 * @head: The head pointer to the list.
 */
void free_alias_list(alias_t *head)
{
	if (head)
	{
		free_alias_list(head->link);
		free(head->shrt);
		free(head->full);
		free(head);
	}
}

int main(void)
{
	char *alias = NULL, *expanded = NULL;
	int shrt_len = 0, full_len = 0;
	alias_t *head = NULL, *node;

	split_alias("push='smore and'", &alias, &expanded, &shrt_len, &full_len);
	node = add_alias(&head, &alias, &expanded, &shrt_len, &full_len);
	split_alias("p='git push origin main'", &alias, &expanded, &shrt_len, &full_len);
	node = add_alias(&head, &alias, &expanded, &shrt_len, &full_len);
	print_alias(head);

}