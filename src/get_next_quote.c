int	get_next_quote(char *str)
{
	if (str[end] == '"' && !s_quote)
		d_quote = (d_quote + 1) % 2;
	else if (str[end] == '\'' && !d_quote)
		s_quote = (s_quote + 1) % 2;
	end++;
}
