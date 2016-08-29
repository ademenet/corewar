.name "Dark Hard Burqini"
.comment "You 'r' goin' to taste my anger!"

wall_init1:
	sti		r1, %:wall_init2, %2

wall_init2:
	ld		%0, r7

wall_init3:
	sti		r7, %:live, %1
	sti		r7, %:wall_front, %1
	sti		r7, %:wall_back, %1
	sti		r7, %:proc_plant, %1
	sti		r7, %:proc_plant, %9
	ld		%0, r16

proc_plant:
	live	%0
	fork	%:wall_front
	live	%0
	fork	%:wall_back
	live	%0
	fork	%:live
	live	%0
	fork	%:wall_init3

wall_front:
	live	%0
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	st		r2, -500
	zjmp	%:wall_front

live:
	live	%0
	zjmp	%:live

wall_back:
	live	%0
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	st		r2, 400
	zjmp	%:wall_back
