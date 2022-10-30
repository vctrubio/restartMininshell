#include "../libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		perror("malloc failed!");
		exit(EXIT_FAILURE);
	}
	ft_memset(new_ptr, 0, size);
	ft_memcpy(new_ptr, ptr, size); // void	*ft_memcpy(void *dest, const void *src, size_t n)
	free(ptr);
	return (new_ptr);
}
