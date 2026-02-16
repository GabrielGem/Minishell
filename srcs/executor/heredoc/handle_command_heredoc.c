int	handle_command_heredoc(t_ast_node *leaf, t_data *context)
{
	t_command	*cmd;
	t_list	*list;
	t_redir	*redir;
	char	*name;
	void	*fd;

	cmd = (t_command *)leaf;
	list = cmd->redirects;
	while (list)
	{
		redir = (t_redir *)list->content;
		if (redir->type == HEREDOC)
		{
			name = generate_unique_name();
			fd = (void *)(long)process_heredoc(redir->filename, name, context);
			ft_lstadd_back(&context->fds, fd);
			free(redir->filename);
			redir->filename = name;
		}
		list = list->next;
	}
}

static char	*generate_unique_name(void)
{
	static int	i;
	char		*name;
	char		*num;
	char		*temp;

	num = ft_itoa(i++);
	address = ft_uitoa_base((unsigned long int)num, "0123456789abcdef");
	temp = ft_strjoin("/tmp/.heredoc_temp_", address);
	name = ft_strjoin(temp, num);
	free(temp);
	return (name);
}
