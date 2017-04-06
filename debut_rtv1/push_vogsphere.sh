git add -A
git commit -m "$1"
git push

cp -R	Makefile	\
		auteur		\
		c_maths		\
		includes	\
		libft		\
		rtv1		\
		sources		\
		src_cl		 /Users/fjanoty/Documents/school/rtv1;

cd  /Users/fjanoty/Documents/school/rtv1;
git add -A;
git commit -m "$1" && git push
