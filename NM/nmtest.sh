echo "\nTests sur NM :"
echo "Tests sur les fichiers objets .o"
./ft_nm obj/*.o > tmp && nm obj/*.o > tmp2 && diff tmp tmp2
#./ft_nm /usr/lib/*.o > tmp && nm /usr/lib/*.o > tmp2 && diff tmp tmp2
echo "Tests sur les fichiers binaires"
./ft_nm nm-otool-tests/32_exe_hard > tmp && nm nm-otool-tests/32_exe_hard > tmp2 && diff tmp tmp2
./ft_nm nm-otool-tests/64_bundle > tmp && nm nm-otool-tests/64_bundle > tmp2 && diff tmp tmp2
./ft_nm nm-otool-tests/64_exe_easy > tmp && nm nm-otool-tests/64_exe_easy > tmp2 && diff tmp tmp2
./ft_nm nm-otool-tests/64_exe_hard > tmp && nm nm-otool-tests/64_exe_hard > tmp2 && diff tmp tmp2
./ft_nm nm-otool-tests/64_exe_medium > tmp && nm nm-otool-tests/64_exe_medium > tmp2 && diff tmp tmp2
./ft_nm nm-otool-tests/object_easy > tmp && nm nm-otool-tests/object_easy > tmp2 && diff tmp tmp2
./ft_nm nm-otool-tests/object_medium > tmp && nm nm-otool-tests/object_medium > tmp2 && diff tmp tmp2
./ft_nm nm-otool-tests/64_lib_dynamic_hard > tmp && nm nm-otool-tests/64_lib_dynamic_hard > tmp2 && diff tmp tmp2
./ft_nm nm-otool-tests/64_lib_dynamic_medium > tmp && nm nm-otool-tests/64_lib_dynamic_medium > tmp2 && diff tmp tmp2
#./ft_nm nm-otool-tests/lib_archive_medium > tmp && nm nm-otool-tests/lib_archive_medium > tmp2 && diff tmp tmp2
./ft_nm ft_nm > tmp && nm ft_nm > tmp2 && diff tmp tmp2
#./ft_nm ft_otool > tmp && nm ft_otool > tmp2 && diff tmp tmp2
./ft_nm /bin/bash > tmp && nm /bin/bash > tmp2 && diff tmp tmp2
#./ft_nm /usr/bin/python > tmp && nm /usr/bin/python > tmp2 && diff tmp tmp2
#./ft_nm /usr/bin/audiodevice > tmp && nm /usr/bin/audiodevice > tmp2 && diff tmp tmp2
echo "Tests sur les bibliotheques dynamiques .so"
./ft_nm /usr/lib/*/*.so > tmp && nm /usr/lib/*/*.so > tmp2 && diff tmp tmp2
echo "Tests sur les bibliotheques dynamiques .dylib"
./ft_nm /usr/lib/*/*.dylib > tmp && nm /usr/lib/*/*.dylib > tmp2 && diff tmp tmp2
