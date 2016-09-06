.name "Dark Hard Burqini"
.comment "You 'r' goin' to taste my anger!"

wall_init:
	sti		r1, %:live, %1
	sti		r1, %:wall_front, %1
	sti		r1, %:wall_back, %1
	sti		r1, %:proc_plant, %1
	sti		r1, %:proc_plant, %9
	ld		%0, r16

proc_plant:
	live	%0
	fork	%:wall_front
	live	%0
	fork	%:wall_back
	live	%0
	fork	%:live
	live	%0
	fork	%:wall_init

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
