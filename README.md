# miniRT - Mini Ray Tracer (Graphics engine)

## Installation

```sh
cd miniRT
make
./miniRT scenes/ (сцена на выбор. внутри файла .rt можно добавлять фигуры, источники света или поменять координаты и направление камеры).
```
## Example:

```sh
cd miniRT
make
./miniRT scenes/map.rt --save
```
второй аргумент --save сигнализирует о намерении сохранить отрисованный кадр в формате .BMP <br>
Сохраненный кадр с аналогичным названием и расширением .BMP появится в папке scenes. <br>

> Note: <br>
> Библиотека работает только с MacOS.<br>
> Сохранение кадра в формате .BMP не использует данную библиотеку. <br>
> В программе реализован корректный выход и освобождение всей динамически аллоцированной памяти.<br>
> Проект успешно защищен в школе Ecole 42 (Сбербанк 21 Казань).<br>
 ## Some Screenshots:
 
 ![cylinder (1)](https://user-images.githubusercontent.com/63866548/115561257-11242700-a2be-11eb-8cff-d414937be578.png)
![cylinder](https://user-images.githubusercontent.com/63866548/115564480-29497580-a2c1-11eb-9b3e-9bd617c5af1b.png)
![map](https://user-images.githubusercontent.com/63866548/115565701-46327880-a2c2-11eb-84ad-63ef78b6df19.png)
