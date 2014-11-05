filename=""
char= "123456789"
environment=useEnvironmentMap
rollout export "export rollout" height:580 width:450
(
	subrollout export1 "export1" height:550
)
rollout select_material_rollout "select from material"
(
	pickbutton pick "add" align:#left offset:[20,0]
	button remove_item "remove" align:#left
	button clear_item "clear" align:#left offset:[13,0]
	listbox selected_material height:6 width:300 offset:[60,-80]
	on pick picked obj do
	(
		if (superclassof obj==GeometryClass or superclassof obj==Shape) then
		(
			if (classof obj.material==VRayMtl) or (classof obj.material==Standardmaterial) then
			(
				if (finditem selected_material.items obj.material.name==0) then
				(
					selected_material.items=append selected_material.items obj.material.name
				)
				else
					messagebox "you have already picked this material!"
			)
			else 
				messagebox "the object selected must have a vray material or standard material!"
		)
		else 
			messagebox "please select an object!"
	)
	on remove_item pressed do
	(
		if(selected_material.selection>0) do
			selected_material.items=deleteItem selected_material.items selected_material.selection
	)
	on clear_item pressed do
	(
		while selected_material.items.count>0 do
		(
			selected_material.items=deleteItem selected_material.items 1
		)
	)
)
rollout select_object_rollout "select objects"
(
	pickbutton pick "add" align:#left offset:[20,0]
	button pick_sel "add_sel" align:#left
	button remove_item "remove" align:#left
	button clear_item "clear" align:#left offset:[13,0]
	listbox selected_objects height:8 width:300 offset:[60,-110]
	on pick picked obj do
	(
		if (superclassof obj==GeometryClass or superclassof obj==Shape) then
		(
			if (classof obj.material==VRayMtl) or (classof obj.material==Standardmaterial) then
			(
				if (finditem selected_objects.items obj.name==0) then
				(
					selected_objects.items=append selected_objects.items obj.name
				)
				else
					messagebox "you have already picked this object!"
			)
			else 
				messagebox "the object selected must have a vray material or standard material!"
		)
		else 
			messagebox "please select an object!"
	)
	on pick_sel pressed do
	(
		for one in selection do
		(
			if (superclassof one==GeometryClass or superclassof one==Shape) do
			(
				if (classof one.material==VRayMtl) or (classof one.material==Standardmaterial) do
				(
					if(finditem selected_objects.items one.name==0) do
						selected_objects.items=append selected_objects.items one.name
				)
			)
		)
	)
	on remove_item pressed do
	(
		if(selected_objects.selection>0) do
			selected_objects.items=deleteItem selected_objects.items selected_objects.selection
	)
	on clear_item pressed do
	(
		while selected_objects.items.count>0 do
		(
			selected_objects.items=deleteItem selected_objects.items 1
		)
	)
)
rollout select_light_rollout "select lights"
(
	pickbutton pick "add" align:#left offset:[20,0]
	button pick_sel "add_sel" align:#left
	button remove_item "remove" align:#left
	button clear_item "clear" align:#left offset:[13,0]
	listbox selected_lights height:8 width:300 offset:[60,-110]
	on pick picked obj do
	(
		if (superclassof obj==light) then
		(
			if (finditem selected_lights.items obj.name==0) then
			(
				selected_lights.items=append selected_lights.items obj.name
			)
			else
				messagebox "you have already picked this light!"
		)
		else 
			messagebox "please select a light!"
	)
	on pick_sel pressed do
	(
		for one in selection do
		(
			if (superclassof one==light) do
			(
				if(finditem selected_lights.items one.name==0) do
					selected_lights.items=append selected_lights.items one.name
			)
		)
	)
	on remove_item pressed do
	(
		if(selected_lights.selection>0) do
			selected_lights.items=deleteItem selected_lights.items selected_lights.selection
	)
	on clear_item pressed do
	(
		while selected_lights.items.count>0 do
		(
			selected_lights.items=deleteItem selected_lights.items 1
		)
	)
)
rollout output_path "output path"
(
	label path_label "output path:" align:#left
	edittext path_name width:300 offset:[60,-20]
	button path_dir "..." height:18 width:20 offset:[180,-23]
	on path_dir pressed do
	(
		filename_temp = getSaveFileName caption:"Render To Texture Object Presets Open" \
		types:"Save Data(*.txt)|*.txt|All(*.*)|*.*" 
		if filename_temp!=undefined do
		(
			filename=filename_temp
			path_name.text=filename
		)
	)
)
rollout run "global parameters"
(
	button run_button "run"
	on run_button pressed do
	(
		if select_material_rollout.selected_material.items.count+select_object_rollout.selected_objects.items.count<0 then
			messagebox "can not choose more than three objects and materials in total!"
		else
		(
			if select_light_rollout.selected_lights.items.count<0 then
				messagebox "can not choose more than three lights!"
			else
			(
				if filename=="" then
					messagebox "please input an output path!"
				else
				(
					filename2=getFilenamePath filename
					filename3=getFilenameFile filename
					filename2+=filename3
					filename2+="_data"
			
					makedir filename2
					fstream=undefined
					if(getfiles filename).count==0 then
					(
						fstream=createfile filename
					)
					else
						fstream=openfile filename mode:"w+"

					contentfile=filename2+"/content.txt"
					contentfile_stream=undefined
					if(getfiles contentfile).count==0 then
					(
						contentfile_stream=createfile contentfile
					)
					else
						contentfile_stream=openfile contentfile mode:"w+"
					
					number_materials=select_material_rollout.selected_material.items.count
					number_objects=select_object_rollout.selected_objects.items.count
					total_number=number_materials+number_objects
					print total_number to:contentfile_stream
					i=0
					for one in select_material_rollout.selected_material.items do
					(
						i+=1
						pic1="object"+char[i]+"_bace.png"
						pic2="object"+char[i]+"_shader.png"
						obj_color=color 255 255 255
						print one to:contentfile_stream
						print pic1 to:contentfile_stream
						print pic2 to:contentfile_stream
						print obj_color to:contentfile_stream
						print 0 to:contentfile_stream
					)
					for one in select_object_rollout.selected_objects.items do
					(
						i+=1
						obj=getnodebyname one
						pic1="object"+char[i]+"_bace.png"
						pic2="object"+char[i]+"_shader.png"
						obj_color=obj.material.diffuse
						print one to:contentfile_stream
						print pic1 to:contentfile_stream
						print pic2 to:contentfile_stream
						print obj_color to:contentfile_stream
						print 0 to:contentfile_stream
					)
					number_lights=select_light_rollout.selected_lights.items.count
					print number_lights to:contentfile_stream
					i=0
					for one in select_light_rollout.selected_lights.items do
					(
						i+=1
						picture_light="light"+char[i]+".png"
						l=getnodebyname one
					--	light_color=l.rgbFilter
						light_color=color 255 255 255
						print one to:contentfile_stream
						print picture_light to:contentfile_stream
						print light_color to:contentfile_stream
						print 100 to:contentfile_stream
					)
					close contentfile_stream
					
					print "this file is just for test" to:fstream
					close fstream
					
	--				fopenexr.setLayerOutputFormat 0 1
	--				fopenexr.setLayerOutputType 0 0 --openexr format
					themat1 = mental_ray ()
					themat1.name ="mental_ray1"
					themat1.surface = qkcolimo ()
					themat1.Surface.Mask = on
					--themat1.Surface.coord_shader = Bitmaptexture \
					--fileName:"C:\Users\Administrator\Documents\3dsMax\sceneassets\images/i2.jpg"
					themat2 = mental_ray ()
					themat2.name = "mental_ray2"
					themat2.surface = qkcolimo ()
					themat2.Surface.Mask = off
					--themat2.Surface.coord_shader = Bitmaptexture \
					--fileName:"C:\Users\Administrator\Documents\3dsMax\sceneassets\images/i2.jpg"
					--if qualityBox.checked then themat2.Surface.quality=1 else themat2.Surface.quality=0
					
					object_array_temp=for one in objects where (superclassof one==geometryclass or superclassof one==Shape) collect one
					object_array=for one in object_array_temp where one.material!=undefined collect one
					material_array=for one in object_array collect one.material
					selected_material=#()
					
					for one in select_material_rollout.selected_material.items do
					(
						selected_material_temp=#()
						
						for obj in object_array do
						(
							if obj.material.name==one do
							(
								append selected_material_temp obj
							)
						)
						append selected_material selected_material_temp
					)
					
					--print selected_material
					i="1"
					j=0
					for one in select_material_rollout.selected_material.items do
					(
						i=i+"1"
						j+=1
						themat_temp=copy selected_material[j][1].material
						themat_temp.name="mymat"+i
						themat_temp.diffuse=color 255 255 255
						if classof themat_temp==VRayMtl do themat_temp.texmap_diffuse=undefined
						if classof themat_temp==Standardmaterial do themat_temp.diffusemap=undefined
						for obj in selected_material[j] do
						(
							obj.material=themat_temp
						)
					)
					for one in select_object_rollout.selected_objects.items do
					(
						i=i+"1"
						obj=getnodebyname one
						judge=false
						if classof obj.material==Standardmaterial do judge=true
						if classof obj.material==VRayMtl do judge=true
						if judge do
						(
							themat_temp=copy obj.material
							themat_temp.name="mymat"+i
							obj.material=themat_temp
							themat_temp.diffuse=color 255 255 255
							if classof obj.material==VRayMtl do themat_temp.texmap_diffuse=undefined
							if classof obj.material==Standardmaterial do themat_temp.diffusemap=undefined
						)
					)
					actionMan.executeAction 0 "50031"--render scene
					bm = GetLastRenderedImage copy:false
					bm.gamma=1.0
					filename4=filename2+"/bace.png"
					bm.filename=filename4
					save bm
					messagebox "bace"
					j=0
					for item in select_material_rollout.selected_material.items do
					(
						j+=1
						for one in selected_material[j] do
						(
							one.material.diffuse=color 0 0 0
						)
						actionMan.executeAction 0 "50031"--render scene
						bm = GetLastRenderedImage copy:false
						bm.gamma=1.0
						bm.filename=filename2+"/object"+char[j]+"_bace.png"
						save bm
						for one in selected_material[j] do
						(
							one.material.diffuse=color 255 255 255
						)
					)
					for one in select_object_rollout.selected_objects.items do
					(
						j+=1
						obj=getnodebyname one
						obj.material.diffuse=color 0 0 0
						actionMan.executeAction 0 "50031"--render scene
						bm = GetLastRenderedImage copy:false
						bm.gamma=1.0
						bm.filename=filename2+"/object"+char[j]+"_bace.png"
						save bm
						obj.material.diffuse=color 255 255 255
					)
					messagebox "objects"
					for one in lights do
					(
						if superclassof one==light do
							one.on=off
					)
					j=0
					for one in select_light_rollout.selected_lights.items do
					(
						j+=1
						lig=getnodebyname one
						lig.on=on
						actionMan.executeAction 0 "50031"--render scene
						bm = GetLastRenderedImage copy:false
						bm.gamma=1.0
						bm.filename=filename2+"/light"+char[j]+".png"
						save bm
						lig.on=off
					)
					messagebox "lights"
					
						useEnvironmentMap = off
					render_current=renderers.current
					renderers.current=mental_ray_renderer()
					
					for one in object_array do
					(
						if classof one.material==Standardmaterial do
						(
							--my code
							reflect = one.material.reflectionMap
							reflectOn = one.material.reflectionMapEnable
						--	refract = one.material.refractionMap
						--	refractOn = one.material.refractionMapEnable
							one.material=copy themat2
							if reflectOn and reflect != undefined do
							(
								one.material.Surface.Reflection=on
							)
						--	if refractOn and refract ! undefined do
						--	(
						--		one.material.Surface.Refraction=on
						--		one.material.Surface.ior=ior
						--	)	
						)
						if classof one.material==VrayMtl do
						(
							reflect=one.material.Reflection
							refract=one.material.Refraction
							ior=one.material.refraction_ior
							one.material=copy themat2
							if reflect!=color 0 0 0 do
							(
								one.material.Surface.Reflection=on
							)
							if(refract!=color 0 0 0) do
							(
								one.material.Surface.Refraction=on
								one.material.Surface.ior=ior
							)
						)
					)
					j=0
					for item in select_material_rollout.selected_material.items do
					(
						j+=1
						for one in selected_material[j] do
						(
							one.material.Surface.mask=on
						)
						actionMan.executeAction 0 "50031"--render scene
						bm = GetLastRenderedImage copy:false
						--if qualityBox.checked then bm.gamma=1.0 else bm.gamma=2.2
						bm.gamma=1.0
						bm.filename=filename2+"/object"+char[j]+"_shader.png"
						save bm
						for one in selected_material[j] do
						(
							one.material.Surface.mask=off
						)
					)
					for one in select_object_rollout.selected_objects.items do
					(
						j+=1
						obj=getnodebyname one
						obj.material.Surface.mask=on
						actionMan.executeAction 0 "50031"--render scene
						bm = GetLastRenderedImage copy:false
						--if qualityBox.checked then bm.gamma=1.0 else bm.gamma=2.2
						bm.gamma=1.0
						bm.filename=filename2+"/object"+char[j]+"_shader.png"
						save bm
						obj.material.Surface.mask=off
					)
					messagebox "texture"
					--actionMan.executeAction 0 "50031"--render scene
					renderers.current=render_current
					for one in lights do
					(
						if superclassof one==light do
						one.on=on
					)
					for i=1 to object_array.count do
					(
						object_array[i].material=material_array[i]
					)
					if(environment) do
						useEnvironmentMap = on
				)
			)
		)
	)
)
createdialog export
AddSubRollout export.export1 select_material_rollout
AddSubRollout export.export1 select_object_rollout
AddSubRollout export.export1 select_light_rollout
AddSubRollout export.export1 output_path
AddSubRollout export.export1 run


