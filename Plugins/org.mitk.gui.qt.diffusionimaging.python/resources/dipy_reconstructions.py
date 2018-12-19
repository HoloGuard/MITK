import sys


def get_mitk_sphere():
    """ Return MITK compliant dipy Sphere object.
    MITK stores ODFs as 252 values spherically sampled from the continuous ODF.
    The sampling directions are generate by a 5-fold subdivisions of an icosahedron.
    """
    xyz = np.array([
        0.9756767549555488, 0.9977154378498742, 0.9738192119472443,
        0.8915721200771204, 0.7646073555341725, 0.6231965669156312,
        0.9817040172417226, 0.9870396762453547, 0.9325589150767597,
        0.8173592116492303, 0.6708930871960926, 0.9399233672993689,
        0.9144882783890762, 0.8267930935417315, 0.6931818659696647,
        0.8407280774774689, 0.782394344826989, 0.6762337155773353,
        0.7005607434301688, 0.6228579759074076, 0.5505632701289798,
        0.4375940376503738, 0.3153040621970065, 0.1569517536476641,
        -0.01984099037382634, -0.1857690950088067, -0.3200730131503601,
        0.5232435944036425, 0.3889403678268736, 0.2135250052622625,
        0.02420694871807206, -0.1448539951504302, 0.5971534158422009,
        0.4482053228282282, 0.2597018771197477, 0.06677517278138323,
        0.6404616222418184, 0.4782876117785159, 0.2868761951248767,
        0.6459894362878276, 0.4789651252338281, 0.3200724178002418,
        0.4973180497018747, 0.6793811951363423, 0.8323587928990375,
        0.9308933612987835, 0.4036036036586492, 0.5984781165037405,
        0.7817280923310203, 0.9140795130247613, 0.4809905907165384,
        0.6759621154318279, 0.8390728924802671, 0.5347729120192694,
        0.7094340284155564, 0.5560356639783846, 0.2502538949373057,
        0.3171352000240629, 0.3793963897789465, 0.4231100429674418,
        0.4410301813437042, 0.4357529867703999, 0.5208717223808415,
        0.5850086433327374, 0.611055499882272, 0.6009463532173235,
        0.6305067000562991, 0.7188806066405239, 0.7654898954879897,
        0.7616477696596397, 0.7997756996573342, 0.8700831379830764,
        0.8872031228985237, 0.9155019734809123, 0.9568003701205341,
        -0.4375932291383153, -0.3153035222278598, -0.1569515927579475,
        0.0198407706589918, 0.1857686171195431, -0.2644927501381796,
        -0.1064219080255857, 0.07849995612144045, 0.2583107784678281,
        -0.04938676750055992, 0.1358448755096817, 0.3243479900672576,
        0.1811879481039926, 0.3692668145365748, 0.3890115016151001,
        -0.6231952788307174, -0.4943551945928708, -0.319458133528771,
        -0.1156489798772063, 0.08328895892415776, -0.4789641985801549,
        -0.3127252940830145, -0.1059392282183739, 0.1077444781964869,
        0.2912280153186658, -0.2868758523956744, -0.08856892011805101,
        0.1287405357080231, 0.3245517154572714, -0.06677541204276306,
        0.1413542883070481, 0.3408430926744944, 0.1448534358763926,
        0.3374016489097037, -0.2502532651867688, -0.3171345072414974,
        -0.3793956104585266, -0.4231091882680272, -0.4410293135613324,
        -0.09929959410007272, -0.1535127609134815, -0.2052877394623771,
        -0.2436963810571767, 0.08175409117371149, 0.04056025153798869,
        -0.006048944565669369, 0.2686152102237028, 0.2319923070602857,
        0.430309819720559, -0.975676581463901, -0.9977153903038788,
        -0.9738191090293654, -0.8915716840571059, -0.7646064477130079,
        -0.9568001079664734, -0.9598482725023617, -0.9044523389503778,
        -0.7901672201648241, -0.6459882395962464, -0.8872027729137049,
        -0.8582754834679532, -0.7705800268610806, -0.6404605781008121,
        -0.7616472974254324, -0.7008201753656432, -0.5971525097007422,
        -0.6009457148226922, -0.5232427588825813, 0.4943566966479628,
        0.3194596781650836, 0.1156503154178581, -0.0832879858164388,
        0.5222841738261358, 0.3225497922064885, 0.1018140973507329,
        0.5217885230992481, 0.3044789836562512, 0.4873191346491355,
        -0.4973183240635209, -0.6793811856410323, -0.8323586364840968,
        -0.9308931819742911, -0.3374020539278631, -0.5261951664998159,
        -0.7070125356849136, -0.8417962075837926, -0.9155017573317124,
        -0.3408433114184408, -0.5265312606271311, -0.6896418460594331,
        -0.7997755164970677, -0.3245517106425898, -0.4925847482169691,
        -0.6305065080228541, -0.2912277152063287, -0.4357526334612896,
        0.7901679726328494, 0.9044526665335126, 0.9598484396937114,
        0.7705806468939737, 0.858275831469383, 0.7008207681995118,
        -0.4036039458806759, -0.2583110138480089, -0.0784999126587471,
        0.1064223584250461, 0.264493571710179, -0.4809907334514471,
        -0.3243480295764106, -0.1358446002697818, 0.04938746901646566,
        -0.5347730026038946, -0.3692667658371347, -0.1811875286592425,
        -0.5560358190148772, -0.3890114324926668, -0.5505634949474449,
        0.8417963565884857, 0.7070125813068046, 0.5261950179989611,
        0.6896418985458221, 0.5265311900255359, 0.4925848265160583,
        0.2436972866599269, 0.2052886581368649, 0.153513629451971,
        0.09930039009433847, 0.006049691633511915, -0.04055950638179381,
        -0.08175337578691833, -0.2319919155781195, -0.2686148310916902,
        -0.430309819678344, -0.02420720081803753, -0.2135248270679241,
        -0.3889397838050994, -0.2597016312374675, -0.4482046405142344,
        -0.4782867918076852, -0.1018130528605821, -0.322548598821141,
        -0.5222830294256716, -0.6708921376896406, -0.304478224282928,
        -0.5217878437313506, -0.6931813485878851, -0.4873188675145023,
        -0.6762335873429084, -0.6228580878699612, -0.6110548409057,
        -0.5850080622199078, -0.5208712693637837, -0.7654894328832393,
        -0.7188802647693375, -0.8700828159137221, -0.8173587433845655,
        -0.9325588839421305, -0.9870397834787261, -0.9817039872478999,
        -0.8267930492778305, -0.9144884914916022, -0.9399235077793813,
        -0.7823945479956939, -0.8407283372889187, -0.7005610213599369,
        -0.1077438933887955, 0.1059400956623477, 0.3127262866621893,
        -0.1287403742204129, 0.08856921814263634, -0.1413545191115968,
        -0.9140794058749131, -0.7817279594934516, -0.5984781448346268,
        -0.8390728949381593, -0.6759620794963979, -0.709434131000089,
        -0.1778161375899129, -0.06053925384414331, 0.07929679392711581,
        0.222673458561735, 0.3458247516791153, 0.4366423972091846,
        0.01030826616734189, 0.1591522280204451, 0.3173816763430465,
        0.4549463955350546, 0.5521270265729551, 0.2292788658415479,
        0.3973400932411465, 0.5502139834879405, 0.6594089221868847,
        0.4476465561008348, 0.6096570464011057, 0.7343998566036512,
        0.629214796874201, 0.7646693979379596, 0.7580253719184178,
        -0.5980610514568761, -0.5101530988159087, -0.382225667160838,
        -0.2244621267538426, -0.06301328229424107, 0.07805400320688782,
        -0.4311039309963852, -0.3079662136138592, -0.1501157132113724,
        0.01750888497279251, 0.1650825345160538, -0.2148810450151756,
        -0.06090095222676627, 0.1073128739652992, 0.2584097661066967,
        0.02655484252908358, 0.1901297170957776, 0.3420822257932489,
        0.2531835106264871, 0.4022303494272352, -0.07805410188638827,
        -0.1080255529483224, -0.1376217050758367, -0.1609000070073124,
        -0.1740018618448228, 0.09827676798573926, 0.083291898217249,
        0.06127443921955168, 0.03526739273256396, 0.2991139104294396,
        0.2941068360088736, 0.2692865316145088, 0.4942032775296958,
        0.4857723178878524, 0.6512069539966677, -0.9161616153729886,
        -0.9396953110011561, -0.9204280785344878, -0.8462030522374957,
        -0.7293237120999879, -0.8470541513588044, -0.8482966176587544,
        -0.7977006542517769, -0.6951661565374421, -0.566558592627622,
        -0.7243096319272092, -0.6931460376496088, -0.6140043047773551,
        -0.5016343691560573, -0.5520254073275178, -0.4928644880867128,
        -0.403575153350467, -0.3587591578566765, -0.2886351685087218,
        0.5980613131647216, 0.5101532951859686, 0.382225843595672,
        0.2244622808787926, 0.06301334452030186, 0.6944632949786616,
        0.5955168212825119, 0.4473425940100297, 0.2700417838303327,
        0.7724043956082883, 0.6553545192922715, 0.4871408620353512,
        0.8097301284690857, 0.6725220182496192, 0.8002534097038426,
        -0.4366431953633789, -0.5869882376922511, -0.7332080507197046,
        -0.8450980113065225, -0.9041113586460733, -0.4022310083998925,
        -0.554596445154436, -0.6925605687496104, -0.7854318984598006,
        -0.8250621271173465, -0.3420827953668352, -0.4840440064641756,
        -0.6033456975789954, -0.6777531805937266, -0.2584102557043402,
        -0.3819753792546441, -0.4821906665520286, -0.1650828712784331,
        -0.270790845781693, 0.9161619708326184, 0.9396956424389374,
        0.9204283182965946, 0.8462032095340455, 0.7293238793541417,
        0.9749588444840027, 0.9879501207294071, 0.942053498973333,
        0.8348196077814718, 0.9950795014807369, 0.9818515654328379,
        0.9027098746674149, 0.9581801446138297, 0.9118246030313639,
        0.8703772282258925, 0.1778171059718252, 0.06053992567271226,
        -0.07929659020903117, -0.2226737578340799, -0.345825401239635,
        0.2886360377097776, 0.1672516508448342, 0.02000533874392893,
        -0.1285435155191929, -0.2531843553864728, 0.403575906447316,
        0.2774342678683828, 0.1245598363284875, -0.02655554762561945,
        0.5016349858535857, 0.3695530582277636, 0.2148806720954671,
        0.5665590425344393, 0.431103930292903, 0.5869876102086139,
        0.7332077514676827, 0.845098078457225, 0.9041116580482536,
        0.7182616282077119, 0.8617334421407644, 0.9490975365686583,
        0.8223898048944452, 0.9416915744235097, 0.8729720010540123,
        0.1080256414522809, 0.1376220280275969, 0.1609005865750696,
        0.1740026689030255, 0.2707904196202965, 0.3196768235430837,
        0.3552546724685221, 0.3677018240803483, 0.3587598208776521,
        0.4821901792282771, 0.5389508449256169, 0.5637713635689835,
        0.5520258363563475, 0.6777529577987501, 0.7231337276202411,
        0.724309982145211, 0.8250622687013296, 0.8470545173149734,
        0.1285429999155006, -0.02000532948058562, -0.1672511147059996,
        -0.1245600244829796, -0.2774338902981233, -0.3695528631494325,
        -0.09827641615811868, -0.2700412859530667, -0.4473420975374328,
        -0.5955164071695848, -0.6944629164413806, -0.2991130971968019,
        -0.4871400501186961, -0.6553538941234454, -0.7724039524031648,
        -0.4942022299541438, -0.6725212074710563, -0.8097296395344389,
        -0.6512059956089504, -0.8002528392148971, -0.7580246814516085,
        -0.3677014077761052, -0.3552545716101517, -0.3196770257819652,
        -0.5637712030900536, -0.5389510214534028, -0.7231336172569296,
        -0.8348194119106425, -0.9420533966954356, -0.9879499956150448,
        -0.9749586635216289, -0.9027097279159257, -0.9818515951566739,
        -0.9950795477220543, -0.9118244750171576, -0.9581802235578871,
        -0.8703770126934449, -0.0175091339170676, 0.1501155140512474,
        0.3079660822386824, -0.1073133727582037, 0.06090046334304851,
        -0.1901304002696938, -0.9490974969653682, -0.8617336589899791,
        -0.7182621005240754, -0.5521276321758419, -0.941691783045487,
        -0.8223901593137167, -0.6594093292610237, -0.872972144171723,
        -0.7343999908188845, -0.7646691446910742, 0.6951665021597787,
        0.7977009700656229, 0.8482969664746548, 0.6140047811934269,
        0.6931464276818936, 0.4928650597255946, -0.4549467775084718,
        -0.3173815862988101, -0.1591515620353438, -0.01030716362341688,
        -0.5502140363721867, -0.3973395475484636, -0.2292777334167206,
        -0.609656670182737, -0.4476455277450017, -0.6292139442700462,
        0.7854319364049284, 0.6925603649758249, 0.5545959620739339,
        0.6033453603619342, 0.4840435291285519, 0.3819748711371402,
        -0.03526641653115874, -0.06127364342066123, -0.0832913202753871,
        -0.2692854573778917, -0.2941058574917593, -0.4857712605383084,
        -0.1282040992012934, 0.02998172476739921, 0.2130449739264662,
        0.394354771181159, 0.5438573645627299, 0.6488215902264565,
        -0.1901340637026595, -0.02057293935230464, 0.1720544722828635,
        0.3534794142829396, 0.4950335464190314, -0.252933321812349,
        -0.07636778766011496, 0.1169519253626288, 0.2909961752861106,
        -0.304612640171253, -0.1271903099934383, 0.0580070042064605,
        -0.3366056805211806, -0.1653138037361849, -0.3496821715684524,
        0.6714420577705413, 0.8002044514563711, 0.9106424580428781,
        0.9742808059046055, 0.9805708386415104, 0.9441720387917811,
        0.7350956003099328, 0.8682639008659977, 0.9653353535299492,
        0.9995536316680411, 0.9755844796257857, 0.7728091190204586,
        0.8918537226509272, 0.9597077065970592, 0.9637247890765801,
        0.767530944505584, 0.857374860312736, 0.8948082473172733,
        0.7201359303293944, 0.7802583897718675, -0.9441722324566724,
        -0.8608166107545396, -0.7207644955095487, -0.5303678229575245,
        -0.3211867088850157, -0.9096404828216634, -0.7967975927156801,
        -0.620601831095295, -0.4039985827676406, -0.8241231220089414,
        -0.6757043639889994, -0.4726959329165278, -0.6854057579633669,
        -0.5106159168102177, -0.5164821811548767, -0.3130828685601688,
        -0.128054626578418, 0.09418349997750548, 0.3239109228229815,
        0.523048087763098, -0.3043330399192493, -0.09531787499064681,
        0.146419102006115, 0.3786227553496849, 0.5638039035645359,
        -0.2789925774668332, -0.05252850546893189, 0.1924160430438771,
        0.4101897544477446, -0.2358533016570041, -0.006318969895916147,
        0.2236016867495729, -0.1820659309330632, 0.03496843200875603,
        -0.6714423515894649, -0.8002045390283683, -0.9106424117173109,
        -0.9742807748705438, -0.9805709251787237, -0.6691519386893557,
        -0.79626257796142, -0.8909109722488041, -0.9275521423149625,
        -0.6332080201962388, -0.7430051304270751, -0.8108589038018792,
        -0.5581290590099237, -0.6413705283620924, -0.4563600901355626,
        -0.648822290296783, -0.6411378559950974, -0.600293640880965,
        -0.5219527418637842, -0.4191009430775375, -0.7802586188950914,
        -0.7711197529973893, -0.713538182957094, -0.6094980396194888,
        -0.4842093859996422, -0.8948081394501657, -0.8705497953564927,
        -0.7870195954857328, -0.6597854273844109, -0.9637246412193355,
        -0.9132982945459158, -0.8070428410352181, -0.975584505681221,
        -0.9015722073987464, 0.3130823317650696, 0.1280539101236855,
        -0.09418429615654819, -0.3239116283455282, -0.523048586255087,
        0.1989845274738189, -0.01970764286946627, -0.2653151882168217,
        -0.4936479477555078, 0.05597369301027853, -0.1852629737758222,
        -0.4302072668465533, -0.09867461327158224, -0.3387557568094476,
        -0.2393260112020272, 0.1282040764044601, -0.0299819504088954,
        -0.2130455201840074, -0.3943555879655132, -0.5438582278251758,
        -0.03496843048443223, -0.2252069693946209, -0.4261053308619027,
        -0.5992598174372795, -0.720136706807033, -0.2236017161594696,
        -0.4317330442416767, -0.6250530132529536, -0.7675317913865697,
        -0.4101898771205939, -0.6101488498350025, -0.7728099228904255,
        -0.5638041319099237, -0.7350961954485662, 0.6411372723067146,
        0.6002931843810706, 0.5219523372221417, 0.4191004905746099,
        0.4596949806286311, 0.3916338931244087, 0.2980734064957148,
        0.226741584116328, 0.1432114770939381, -0.02097489882147943,
        0.8608164411414747, 0.7207644427956729, 0.5303678926086439,
        0.3211867913977836, 0.9015721838250796, 0.7879881821713033,
        0.6114960278478284, 0.3951892122332402, 0.1820657113417612,
        0.8070430398170311, 0.6574928275930984, 0.4544842943197335,
        0.2358529185889448, 0.6597856586149884, 0.4841878538357612,
        0.2789921022280572, 0.4842093252521232, 0.3043325272261384,
        0.5992589358516202, 0.4261046359672609, 0.2252066549797059,
        0.6250522113657903, 0.4317325950511361, 0.6101482870567641,
        0.9096403689902206, 0.9275522217134882, 0.8909112253661301,
        0.796262827475376, 0.6691520068054228, 0.8241233338640371,
        0.810859375773786, 0.7430057321681839, 0.6332085061147845,
        0.6854064426268304, 0.6413714065577412, 0.5581299045184589,
        0.5164832226272315, 0.4563611494403301, 0.3496833143594963,
        -0.3951892821849063, -0.6114960336943951, -0.787988199289983,
        -0.4544844137443082, -0.657492739431111, -0.484187939006181,
        0.4936478319326018, 0.2653148405479006, 0.01970714938077021,
        -0.1989850169013517, 0.4302075642722875, 0.1852629793843341,
        -0.0559739158243807, 0.3387563694841473, 0.09867487876932232,
        0.2393267951217032, -0.999553621201999, -0.9653354239158236,
        -0.8682642090770526, -0.9597077173597477, -0.8918540989344099,
        -0.8573751662344773, -0.2980738893651726, -0.3916343988495664,
        -0.4596955428592778, -0.4950341577852201, -0.1432117197792371,
        -0.2267418620329016, -0.2909964852939082, 0.02097514873862574,
        -0.05800679989935065, 0.1653145532988453, -0.3786231842883476,
        -0.1464197032303796, 0.09531724619007391, -0.1924163631703616,
        0.05252803743712917, 0.006318730357784829, -0.3534800054422614,
        -0.1720548071373146, 0.02057294660420643, 0.190134278339324,
        -0.1169519894866824, 0.07636807502743861, 0.2529338262925594,
        0.1271908635410245, 0.3046134343217798, 0.3366066958443542,
        0.6094980941008995, 0.7135382519498201, 0.7711196978950583,
        0.7870198804193677, 0.8705500304441893, 0.9132984713369965,
        0.403998910419839, 0.62060207699311, 0.7967976318501995,
        0.4726965405256068, 0.6757048258462731, 0.5106167801856609])

    n = int(xyz.shape[0] / 3)
    x = xyz[:n]
    y = xyz[n:2 * n]
    z = xyz[2 * n:]

    for i in range(n):
        v = np.array([x[i], y[i], z[i]])
        norm = np.linalg.norm(v)
        if norm > 0:
            v /= norm
        x[i] = v[0]
        y[i] = v[1]
        z[i] = v[2]

    s = sphere.Sphere(x=x, y=y, z=z)
    return s


error_string = None
del error_string
try:
    import dipy.direction.peaks as dpp
    from dipy.reconst.shore import ShoreModel
    from dipy.reconst.shm import CsaOdfModel, OpdtModel, SphHarmModel
    import dipy.reconst.sfm as sfm
    from dipy.reconst.csdeconv import auto_response, ConstrainedSphericalDeconvModel
    from dipy.core import sphere
    import numpy as np
    from dipy.core.gradients import gradient_table
    import SimpleITK as sitk

    print('DIPY Reconstructions')
    data = sitk.GetArrayFromImage(in_image)
    bvals = np.array(bvals)
    bvecs = np.array(bvecs)

    # create dipy Sphere
    sphere = get_mitk_sphere()
    odf = None
    model = None
    gtab = gradient_table(bvals, bvecs)

    if mask is not None:
        mask = sitk.GetArrayFromImage(mask)
        print(mask.shape)


    # fit selected model
    sh_coeffs = None
    odf = None
    if model_type == '3D-SHORE':
        print('Fitting 3D-SHORE')
        print("radial_order: ", radial_order)
        print("zeta: ", zeta)
        print("lambdaN: ", lambdaN)
        print("lambdaL: ", lambdaL)
        model = ShoreModel(gtab, radial_order=radial_order, zeta=zeta, lambdaN=lambdaN, lambdaL=lambdaL)
        asmfit = model.fit(data)
        odf = asmfit.odf(sphere)
    elif model_type == 'CSA-QBALL':
        print('Fitting CSA-QBALL')
        print("sh_order: ", sh_order)
        print("smooth: ", smooth)
        model = CsaOdfModel(gtab=gtab, sh_order=sh_order, smooth=smooth)
        sh_coeffs = model.fit(data, mask=mask).shm_coeff
    elif model_type == 'SFM':
        print('Fitting SFM')
        print("fa_thr: ", fa_thr)
        response, ratio = auto_response(gtab, data, roi_radius=10, fa_thr=fa_thr)
        model = sfm.SparseFascicleModel(gtab, sphere=sphere,
                                        l1_ratio=0.5, alpha=0.001,
                                        response=response[0])
        odf = model.fit(data, mask=mask).odf(sphere)
    elif model_type == 'CSD':
        print('Fitting CSD')
        print("sh_order: ", sh_order)
        print("fa_thr: ", fa_thr)
        response, ratio = auto_response(gtab, data, roi_radius=10, fa_thr=fa_thr)
        model = ConstrainedSphericalDeconvModel(gtab, response, sh_order=sh_order)
        sh_coeffs = model.fit(data).shm_coeff
    elif model_type == 'Opdt':
        print('Orientation Probability Density Transform')
        print("sh_order: ", sh_order)
        print("smooth: ", smooth)
        model = OpdtModel(gtab=gtab, sh_order=sh_order, smooth=smooth)
        sh_coeffs = model.fit(data, mask=mask).shm_coeff
    else:
        raise ValueError('Model type not supported. Available models: 3D-SHORE, CSA-QBALL, SFM, CSD, Opdt')

    if odf is not None:
        odf = np.nan_to_num(odf)
        print('Preparing ODF image')
        odf_image = sitk.Image([data.shape[2], data.shape[1], data.shape[0]], sitk.sitkVectorFloat32, len(sphere.vertices))
        for x in range(data.shape[2]):
            for y in range(data.shape[1]):
                for z in range(data.shape[0]):
                    if mask is not None and mask[z, y, x] == 0:
                        continue
                    odf_image.SetPixel(x, y, z, odf[z, y, x, :])
        odf_image.SetOrigin(in_image.GetOrigin())
        odf_image.SetSpacing(in_image.GetSpacing())
        odf_image.SetDirection(in_image.GetDirection())
    elif sh_coeffs is not None:
        sh_coeffs = np.nan_to_num(sh_coeffs)
        print('Preparing SH image')
        sh_image = sitk.Image([sh_coeffs.shape[2], sh_coeffs.shape[1], sh_coeffs.shape[0]], sitk.sitkVectorFloat32, sh_coeffs.shape[3])
        for x in range(sh_coeffs.shape[2]):
            for y in range(sh_coeffs.shape[1]):
                for z in range(sh_coeffs.shape[0]):
                    if mask is not None and mask[z, y, x] == 0:
                        continue
                    sh_image.SetPixel(x, y, z, sh_coeffs[z, y, x, :])
        sh_image.SetOrigin(in_image.GetOrigin())
        sh_image.SetSpacing(in_image.GetSpacing())
        sh_image.SetDirection(in_image.GetDirection())

    if num_peaks > 0:

        print('Calculating peaks')
        sys.stdout.flush()
        # calculate peak image
        data = np.nan_to_num(data)
        sf_peaks = dpp.peaks_from_model(model,
                                        data,
                                        sphere,
                                        relative_peak_threshold=relative_peak_threshold,
                                        min_separation_angle=min_separation_angle,
                                        return_sh=False, npeaks=num_peaks, parallel=True,
                                        mask=mask)

        # reshape to be MITK/MRtrix compliant
        s = sf_peaks.peak_dirs.shape
        peaks = sf_peaks.peak_dirs.reshape((s[0], s[1], s[2], num_peaks * 3), order='C')
        peaks = np.nan_to_num(peaks)
        peak_image = sitk.Image([data.shape[2], data.shape[1], data.shape[0]], sitk.sitkVectorFloat32, num_peaks * 3)

        # scale peaks
        max_peak = 1.0
        if normalize_peaks:
            max_peak = np.max(sf_peaks.peak_values)
        if max_peak <= 0:
            max_peak = 1.0
        for x in range(s[0]):
            for y in range(s[1]):
                for z in range(s[2]):
                    for i in range(num_peaks):
                        peaks[x, y, z, i * 3] *= sf_peaks.peak_values[x, y, z, i] / max_peak
                        peaks[x, y, z, i * 3 + 1] *= sf_peaks.peak_values[x, y, z, i] / max_peak
                        peaks[x, y, z, i * 3 + 2] *= sf_peaks.peak_values[x, y, z, i] / max_peak

                    peak_image.SetPixel(z, y, x, peaks[x, y, z, :])

        peak_image.SetOrigin(in_image.GetOrigin())
        peak_image.SetSpacing(in_image.GetSpacing())
        peak_image.SetDirection(in_image.GetDirection())


except Exception as e:
    error_string = str(e)
    print(error_string)

sys.stdout.flush()
