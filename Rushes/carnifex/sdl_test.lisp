(ql:quickload "lispbuilder-sdl")
(sb-int:with-float-traps-masked (:invalid :inexact :overflow)
(sdl:with-init ()
	(sdl:window 800 950)
	(sdl:draw-surface (sdl:load-image "./01.bmp"))
	(sdl:update-display)
		(sdl:with-events ()
			(:quit-event () t)
			(:video-expose-event () (sdl:update-display)))))
