import 'dart:async';
import 'package:angular2/core.dart';
import 'package:angular2/router.dart';
import 'hero.dart';
import 'hero_service.dart';
@Component(
    selector: 'my-heroes',
    templateUrl: 'heroes_component.html',
    styleUrls: const ['heroes_component.css']
)
class HeroesComponent implements OnInit {
    final Router _router;
    final HeroService _heroService;
    List<Hero> heroes ;
    
    Hero selectedHero;
    HeroesComponent(this._heroService, this._router);
    
    Future<NULL> getHeroes() async{
        heroes = await _heroService.getHeroes();
    }
    void ngOnInit(){
        getHeroes();
    }
    void onSelect(Hero hero){
        selectedHero = hero;
    }
    
    Future<Null> gotoDetail() => _router.navigate([
        'HeroDetail',
        {'id': selectedHero.id.toString()}
    ]);
}

