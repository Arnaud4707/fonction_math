MUGT Multi Usage Graphic ToolBox 
 
## Pour clone le depot avec les sub modules
```
git clone --recurse-submodules git@github.com:Arnaud4707/fonction_math.git
```

## Pour clone les sub modules apres avoir git clone
```
git submodule update --init --recursive
```

## Info

- World 1: Fonction algébrique representer graphiquement
- World 2: Moteur 3D
- World 3: Automate cellulaire (Game Of Life)

## Utilisation

Pour compiler
```
make

make all

make world_1

make world_2

make world_3
```

Pour clean sans supprimer l'executable
```
make clean
```

Pour clean tout
```
make fclean
```

Pour clean et complier
```
make re
```

## Documentation
- https://www.3dgep.com/understanding-the-view-matrix/
- https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html
- http://raphaello.univ-fcomte.fr/IG/ZBuffer/ZBuffer.htm
