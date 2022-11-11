#include "main.h"

/**
 * _exit_th - exits a process
 * @arr_tokens: the array to check for a builtin command
 * @env_head: Head pointer to the linked list of environment variables
 * @buffer: the temporary buffer holding input data
 *
 * Return: void on success,
 * otherwise, NULL
*/
char *_exit_th(char **arr_tokens, env_node *env_head, char *buffer)
{
	int status = 0;

	if (arr_tokens[1])
	{
		status = exit_atoi(arr_tokens[1]);
		if (status == -1)
			return (NULL);
	}
	status %= 256;
	free_env_list(env_head);
	free(arr_tokens);
	free(buffer);
	exit(status);

	return (NULL);
}

/**
 * cd - Changes the present working directory
 * @arr_tokens: The array to check for a builtin command
 * @env_head: Head pointer to list of the environment variables
 * @buffer: The temporary buffer holding input data
 *
 * Return: ok, if successful,
 * otherwise, NULL
*/
char *cd(char **arr_tokens, env_node *env_head, char *buffer)
{
	char *pwd, *oldpwd = getcwd(NULL, 0);

	if (arr_tokens[2])
		return (NULL);

	if (arr_tokens[1])
	{
		if (_strcmp(arr_tokens[1], "-") == 0)
		{
			pwd = _getenv("OLDPWD", env_head);
			if (chdir(pwd) == 0)
			{
				write(1, pwd, _strlen(pwd));
				write(1, "\n", 1);
				update_var_for_cd(env_head, arr_tokens, buffer, pwd, oldpwd);
				return ("ok");
			}
		}
		else if (chdir(arr_tokens[1]) == 0)
		{
			update_var_for_cd(env_head, arr_tokens, buffer, arr_tokens[1], oldpwd);
			return("ok");
		}
	}
	else
	{
		pwd = _getenv("HOME", env_head);
		if (chdir(pwd) == 0)
		{
			update_var_for_cd(env_head, arr_tokens, buffer, pwd, oldpwd);
			return ("ok");
		}
	}
	free(oldpwd);
	return (NULL);
}

/**
 * _env - Prints the list of environment variables.
 * @arr_tokens: Array of tokens.
 * @env_head: Head pointer to linked list.
 * @buffer: Commandline buffer.
 *
 * Return: ok if successful, NULL if failed.
 */
char *_env(char **arr_tokens, env_node *env_head, char *buffer)
{
	if (env_head)
	{
		write(1, env_head->name, _strlen(env_head->name));
		write(1, env_head->equals, 1);
		write(1, env_head->value, _strlen(env_head->value));
		write(1, "\n", 1);
		_env(arr_tokens, env_head->next, buffer);
	}
	else
	{
		free(buffer);
		free(arr_tokens);
	}
	return ("ok");
}

/**
 * _setenv - Sets an environment variable
 * @arr_tokens: The array to check for a builtin command
 * @env_head: Head pointer to the linked list of environment variables
 * @buffer: The temporary buffer holding input data
 *
 * Return: ok on success,
 * otherwise, NULL
*/
char *_setenv(char **arr_tokens, env_node *env_head, char *buffer)
{
	if (arr_tokens[3])
		write_to_stderr("%c: invalid number of arguments\n", NULL, 0, arr_tokens[0], NULL);

	if (!replace_env_node(env_head, arr_tokens[1], arr_tokens[2]))
		write_to_stderr("%c: failed to set variable\n", NULL, 0, arr_tokens[0], NULL);
	free(buffer);
	free(arr_tokens);
	return ("ok");
}

/**
 * _unsetenv - Removes an environment variable.
 * @arr_tokens: The array to check for a builtin command.
 * @env_head: A pointer to the environment variables.
 * @buffer: The temporary buffer holding input data.
 *
 * Return: ok on success,
 * otherwise, NULL
*/
char *_unsetenv(char **arr_tokens, env_node *env_head, char *buffer)
{
	if (arr_tokens[2])
		write_to_stderr("%c: invalid number of arguments\n", NULL, 0, arr_tokens[0], NULL);

	if (!delete_env_node(env_head, arr_tokens[1]))
		write_to_stderr("%c: failed to unset variable\n", NULL, 0, arr_tokens[0], NULL);
	free(buffer);
	free(arr_tokens);
	return ("ok");
}

